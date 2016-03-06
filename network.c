//
// Created by janco on 25-2-16.
//
#include <dev/board.h>
#include <dev/debug.h>
#include <sys/timer.h>
#include <sys/confnet.h>
#include <sys/socket.h>

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <net/route.h>

#include <dev/nicrtl.h>

#include <stdio.h>
#include <io.h>
#include <arpa/inet.h>
#include <pro/dhcp.h>
#include <pro/sntp.h>
#include "network.h"
#include "ntp.h"
#include "jsmn.h"
#include "rtc.h"

void NetworkInit() {
    /* Register de internet controller. */
    if (NutRegisterDevice(&DEV_ETHER, 0, 0)) {
        printf("Registering  failed.");
    }/* Netwerk configureren op dhcp */
    else if (NutDhcpIfConfig(DEV_ETHER_NAME, NULL, 0)) {
        /* Done. */
    }else {
        printf("Ik heb een internet connectie. Ip is: %s", inet_ntoa(confnet.cdn_ip_addr));
    }
}

char* httpGet(char address[]){
    printf("komt in httpget()");
    NutDelay(1000);
    TCPSOCKET* sock = NutTcpCreateSocket();
    char http[150];
    sprintf(http, "GET %s HTTP/1.1\r\nHost: saltyradio.jancokock.me \r\n\r\n", address);
    printf("%s", http);
    NutDelay(100);
    char buffer[250];
    int len = sizeof(http);
    if (NutTcpConnect(sock, inet_addr("62.195.226.247"), 80)) {
        printf("Can't connect to server\n");
    }else{
        FILE *stream;
        stream = _fdopen((int) sock, "r b");
        if(NutTcpSend(sock, http, len) != len){
            printf("Writing headers failed.");
            NutDelay(1000);
        }else{
            printf("Headers writed. Now reading.");
            NutDelay(1000);
            NutTcpReceive(sock, buffer, sizeof(buffer));
                //fread(buffer, 1, sizeof(buffer), stream);
            NutDelay(1000);
            printf(buffer);
        };
        fclose(stream);

    }
    NutTcpCloseSocket(sock);
    int i;
    int enters = 0;
    int t = 0;
    char* content = (char*) calloc(1 , sizeof(buffer));
    for(i = 0; i < strlen(buffer); i++)
    {
        if(enters > 3) {
            enters = 10;
            content[t] = buffer[i];
            t++;
        }
        if(buffer[i] == '\n' || buffer[i] == '\r')
        {
            enters++;
        }
        else if(enters < 10)
        {
            enters = 0;
        }
    }
    content[t] = '\0';
    printf("\nContent size %d \n", t);
    printf("\nContent: %s \n", content);


    return content;
}

void parseAlarmJson(char* content){
    int r;
    int i;
    jsmn_parser p;
    jsmntok_t token[50]; /* We expect no more than 128 tokens */

    jsmn_init(&p);
    r = jsmn_parse(&p, content, strlen(content), token, sizeof(token)/sizeof(token[0]));
    if (r < 0) {
        printf("Failed to parse JSON: %d \n", r);
    }else{
        printf("Aantal tokens found: %d \n", r);
    }

    struct _tm time;
    X12RtcGetClock(&time);
    NutDelay(100);

    for (i = 1; i < r; i++) {
        if (jsoneq(content, &token[i], "hh") == 0) {
            /* We may use strndup() to fetch string value */
            char hh[2];
            sprintf(hh, "%.*s", token[i+1].end-token[i+1].start, content + token[i+1].start);
            printf("Tijd uren: %s\n", hh);
            time.tm_hour = atoi(hh);    //only use when 100% sure input is an integer
            i++;
        }else if (jsoneq(content, &token[i], "mm") == 0) {
            /* We may use strndup() to fetch string value */
            char mm[2];
            sprintf(mm, "%.*s", token[i+1].end-token[i+1].start, content + token[i+1].start);
            printf("Tijd minuten: %s\n", mm);
            time.tm_min = atoi(mm);    //only use when 100% sure input is an integer
            i++;
        }else if (jsoneq(content, &token[i], "ss") == 0) {
            /* We may use strndup() to fetch string value */
            char ss[2];
            sprintf(ss, "%.*s", token[i + 1].end - token[i + 1].start, content + token[i + 1].start);
            printf("Tijd seconden: %s\n", ss);
            time.tm_sec = atoi(ss);     //only use when 100% sure input is an integer
            i++;
        }
    }
}
