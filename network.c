//
// Created by janco on 25-2-16.
//
#include <dev/board.h>
#include <dev/debug.h>
#include <sys/timer.h>
#include <sys/confnet.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

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

#include "alarm.h"
#include "contentparser.h"
#include "jsmn.h"
#include "ntp.h"
#include "network.h"
#include "rtc.h"

bool isReceiving = false;
bool hasNetwork = false;

void NetworkInit() {
    hasNetwork = false;
    /* Register de internet controller. */
    if (NutRegisterDevice(&DEV_ETHER, 0, 0)) {
        printf("Registering  failed. \n");
    }/* Netwerk configureren op dhcp */
    else if (NutDhcpIfConfig(DEV_ETHER_NAME, NULL, 0)) {
        printf("DHCP failed. \n");
    }else {
        printf("Ik heb een internet connectie. Ip is: %s \nMac address is:  %s\n\n", inet_ntoa(confnet.cdn_ip_addr),  ether_ntoa(confnet.cdn_mac));
    }
    NutSleep(100);
    hasNetwork = true;
}

char* getMacAdress(){
    ether_ntoa(confnet.cdn_mac);
}

void httpGet(char address[], void (*parser)(char*)){
    u_long rx_to = 3000;
    isReceiving = true;
    printf("\n\n #-- HTTP get -- #\n");

    TCPSOCKET* sock = NutTcpCreateSocket();

    char buffer[2];
    char* content = (char*) calloc(1 , 800);
    char enters = 0;
    int t = 0;

    if(content == 0){
        printf("Can't calloc memory\n");
    }else if (NutTcpConnect(sock, inet_addr("62.195.226.247"), 80)) {
        printf("Can't connect to server\n");
    }else if (NutTcpSetSockOpt(sock, SO_RCVTIMEO, &rx_to, sizeof(rx_to))){

    }else{
        FILE *stream;
        stream = _fdopen((int) sock, "r+b");

        //Writing http GET to stream
        fprintf(stream, "GET %s HTTP/1.1\r\nHost: saltyradio.jancokock.me \r\n\r\n", address);
        fflush(stream);

        printf("Headers writed. Now reading.");
        NutDelay(500);
        //Removing header:
        while(fgets(buffer, sizeof(buffer), stream) != NULL) {
            if(enters == 4) {
                content[t] = buffer[0];
                t++;
            }else {
                if (buffer[0] == '\n' || buffer[0] == '\r') {
                    enters++;
                }
                else {
                    enters = 0;
                }
            }
        }
        fclose(stream);
    }
    NutTcpCloseSocket(sock);

    content[t] = '\0';
    printf("\nContent size: %d, Content: %s \n", t, content);
    parser(content);
    free(content);

    isReceiving = false;
    return content;
}

bool NetworkIsReceiving(void){
    return isReceiving;
}

bool hasNetworkConnection(void){
    return hasNetwork;
}
