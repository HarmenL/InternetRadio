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
    sprintf(http, "GET %s HTTP/1.1\r\nHost: jancokock.me \r\n\r\n", address);
    printf("%s", http);
    NutDelay(100);
    char buffer[200];
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
    printf("Content size %d\n", t);
    return content;
}
