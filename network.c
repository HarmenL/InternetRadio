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

void httpGet(){
    TCPSOCKET* sock = NutTcpCreateSocket();
    char http[] = "GET /Projecten/projectgroepa6/internetradio/gettimezone.php HTTP/1.1\r\nHost: jancokock.me \r\n\r\n";
    char buffer = (char *) malloc(8);
    int len = sizeof(http);
    if (NutTcpConnect(sock, inet_addr("62.195.226.247"), 80)) {
        printf("Can't connect to sever\n");
    }else{
        FILE *stream;
        stream = _fdopen((int) sock, "r b");
        if(NutTcpSend(sock, http, len) != len){
            printf("Writing headers failed.");
        }else{
            printf("Headers writed. Now reading.");
            while(fread(buffer, 1, sizeof(buffer), stream) > 0){
                printf("%s", buffer);
            };
        };
        fclose(stream);
    }
    NutTcpCloseSocket(sock);
}
