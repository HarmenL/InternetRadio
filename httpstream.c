//
// Created by janco on 10-3-16.
//
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>
#include <sys/version.h>
#include <dev/irqreg.h>

#include "vs10xx.h"
#include <sys/socket.h>
#include <netinet/tcp.h>

#include <sys/confnet.h>

#include <arpa/inet.h>
#include <net/route.h>

#include <dev/board.h>
#include <pro/httpd.h>
#include <pro/dhcp.h>
#include <pro/asp.h>
#include <pro/discover.h>
#include <dev/nicrtl.h>

#include "ntp.h"
#include "httpstream.h"

#define MAX_HEADERLINE 512

bool isStreaming;

TCPSOCKET *sock;
u_short mss = 1460;
u_long rx_to = 3000;
u_short tcpbufsiz = 8760;
FILE *stream;
u_long metaint;

THREAD(Stream, args)
{
    if(stream) {
        PlayMp3Stream(stream, metaint);
    }
    stopStream();
    NutThreadExit();
}

void playStream(char *ipaddr, u_short port, char *radiourl){
    if(isStreaming != true){
        isStreaming = true;
        ConnectStation(sock, inet_addr(ipaddr), port, radiourl, &metaint);
        NutThreadCreate("Stream", Stream, NULL, 1024);
    }
}

void stopStream(){
    isStreaming = false;
    fclose(stream);
    NutTcpCloseSocket(sock);
}

bool HttpIsStreaming(){
    return isStreaming;
}

void ConnectStation(TCPSOCKET *sock, u_long ip, u_short port, char *radiourl, u_long *metaint){
    int rc;
    u_char *line;
    u_char *cp;

    /*
     * Connect the TCP server.
     */
    if ((sock = NutTcpCreateSocket()) == 0)
        printf("Probleem bij het creereen van tcp socket");
    if (NutTcpSetSockOpt(sock, TCP_MAXSEG, &mss, sizeof(mss)))
        printf("Probleem bij het creereen van tcp socket");
    if (NutTcpSetSockOpt(sock, SO_RCVTIMEO, &rx_to, sizeof(rx_to)))
        printf("Probleem bij het creereen van tcp socket");
    if (NutTcpSetSockOpt(sock, SO_RCVBUF, &tcpbufsiz, sizeof(tcpbufsiz)))
        printf("Probleem bij het creereen van tcp socket");

    printf("Connecting %s:%u...", inet_ntoa(ip), port);
    if ((rc = NutTcpConnect(sock, ip, port))) {
        printf("Error: Connect failed with %d\n", ip);
        return 0;
    }
    puts("OK");

    if ((stream = _fdopen((int) sock, "r+b")) == 0) {
        printf("Error: Can't create stream");
        return 0;
    }

    /*
     * Send the HTTP request.
     */
    printf("GET %s HTTP/1.0\n\n", radiourl);
    fprintf(stream, "GET %s HTTP/1.0\r\n", radiourl);
    fprintf(stream, "Host: %s\r\n", inet_ntoa(ip));
    fprintf(stream, "User-Agent: Ethernut\r\n");
    fprintf(stream, "Accept: */*\r\n");
    fprintf(stream, "Icy-MetaData: 1\r\n");
    fprintf(stream, "Connection: close\r\n");
    fputs("\r\n", stream);
    fflush(stream);

    /*
     * Receive the HTTP header.
     */
    line = malloc(MAX_HEADERLINE);
    while(fgets(line, MAX_HEADERLINE, stream)) {

        /*
         * Chop off the carriage return at the end of the line. If none
         * was found, then this line was probably too large for our buffer.
         */
        cp = strchr(line, '\r');
        if(cp == 0) {
            printf("Warning: Input buffer overflow");
            continue;
        }
        *cp = 0;

        /*
         * The header is terminated by an empty line.
         */
        if(*line == 0) {
            break;
        }
        if(strncmp(line, "icy-metaint:", 12) == 0) {
            *metaint = atol(line + 12);
        }
        printf("%s\n", line);
    }
    putchar('\n');

    free(line);
}

int ProcessMetaData(FILE *stream)
{
    u_char blks = 0;
    u_short cnt;
    int got;
    int rc = 0;
    u_char *mbuf;

    /*
     * Wait for the lenght byte.
     */
    got = fread(&blks, 1, 1, stream);
    if(got != 1) {
        return -1;
    }
    if (blks) {
        if (blks > 32) {
            printf("Error: Metadata too large, %u blocks\n", blks);
            return -1;
        }

        cnt = blks * 16;
        if ((mbuf = malloc(cnt + 1)) == 0) {
            return -1;
        }

        /*
         * Receive the metadata block.
         */
        for (;;) {
            if ((got = fread(mbuf + rc, 1, cnt, stream)) <= 0) {
                return -1;
            }
            if ((cnt -= got) == 0) {
                break;
            }
            rc += got;
            mbuf[rc] = 0;
        }

        printf("\nMeta='%s'\n", mbuf);
        free(mbuf);
    }
    return 0;
}


void PlayMp3Stream(FILE *stream, u_long metaint)
{
    size_t rbytes;
    u_char *mp3buf;
    u_char ief;
    int got = 0;
    u_long last;
    u_long mp3left = metaint;

    /*
     * Initialize the MP3 buffer. The NutSegBuf routines provide a global
     * system buffer, which works with banked and non-banked systems.
     */
    if (NutSegBufInit(8192) == 0) {
        puts("Error: MP3 buffer init failed");
        return;
    }

    /*
     * Initialize the MP3 decoder hardware.
     */
    if (VsPlayerReset(0)) {
        puts("Error: MP3 hardware init failed");
        return;
    }

    /*
     * Reset the MP3 buffer.
     */
    ief = VsPlayerInterrupts(0);
    NutSegBufReset();
    VsPlayerInterrupts(ief);
    last = NutGetSeconds();

    while (isStreaming == true) {
        /*
         * Query number of byte available in MP3 buffer.
         */
        ief = VsPlayerInterrupts(0);
        mp3buf = NutSegBufWriteRequest(&rbytes);
        VsPlayerInterrupts(ief);

        /*
         * If the player is not running, kick it.
         */
        if (VsGetStatus() != VS_STATUS_RUNNING) {
            puts("Not running");
            if(rbytes < 1024 || NutGetSeconds() - last > 4UL) {
                last = NutGetSeconds();
                puts("Kick player");
                VsPlayerKick();
            }
        }
        /*
         * Do not read pass metadata.
         */
        if (metaint && rbytes > mp3left) {
            rbytes = mp3left;
        }

        /*
         * Read data directly into the MP3 buffer.
         */
        while (rbytes && (isStreaming == true)) {
            if ((got = fread(mp3buf, 1, rbytes, stream)) > 0) {
                ief = VsPlayerInterrupts(0);
                mp3buf = NutSegBufWriteCommit(got);
                VsPlayerInterrupts(ief);

                if (metaint) {
                    mp3left -= got;
                    if (mp3left == 0) {
                        ProcessMetaData(stream);
                        mp3left = metaint;
                    }
                }

                if(got < rbytes && got < 512) {
                    printf("%lu buffered\n", NutSegBufUsed());
                    NutSleep(250);
                }
                else {
                    NutThreadYield();
                }
            } else {
                break;
            }
            rbytes -= got;
        }

        if(got <= 0) {
            break;
        }
    }
}