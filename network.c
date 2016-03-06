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
    printf("\n Content size %d\n", t);
    printf("\n Content: %s", content);


    return content;
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
    if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
        strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}

void parseJson(char* content){
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
    for (i = 1; i < r; i++) {
        printf("\n Json token: Start: %d, End: %d", token[i].start, token[i].end);
        if (jsoneq(content, &token[i], "tijd") == 0) {
            /* We may use strndup() to fetch string value */
            printf("- Tijd: %.*s\n", token[i+1].end-token[i+1].start,
                   content + token[i+1].start);
            i++;
        }
    }
}
