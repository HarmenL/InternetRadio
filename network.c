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
        printf("Ik heb een internet connectie. Ip is: %s \n\n", inet_ntoa(confnet.cdn_ip_addr));
    }
    NutSleep(100);
    hasNetwork = true;
}

char* httpGet(char address[]){
    isReceiving = true;
    NutDelay(1000);
    //printf("\n\n #-- HTTP get -- #\n");

    TCPSOCKET* sock = NutTcpCreateSocket();

    char http[strlen(address) + 49]; //49 chars based on get command. Change this number if you change the domain name
    sprintf(http, "GET %s HTTP/1.1\r\nHost: saltyradio.jancokock.me \r\n\r\n", address);
    int len = sizeof(http);

    char buffer[800];
    memset(buffer, 0, 800);

    if (NutTcpConnect(sock, inet_addr("62.195.226.247"), 80)) {
        printf("Can't connect to server\n");
    }else{
        //FILE *stream;
        //stream = _fdopen((int) sock, "r b");
        if(NutTcpSend(sock, http, len) != len){
            printf("Writing headers failed.\n");
            NutDelay(1000);
        }else{
            printf("Headers written: %sNow reading...\n", http);
            NutDelay(1000);
            NutTcpReceive(sock, buffer, sizeof(buffer));
            //fread(buffer, 1, sizeof(buffer), stream);
            NutDelay(1200);
            //printf(buffer);
        };
        //fclose(stream);
    }
    NutTcpCloseSocket(sock);
    int i;
    int enters = 0;
    int t = 0;
    char* content = (char*) calloc(1 , sizeof(buffer));
    for(i = 0; i < strlen(buffer); i++)
    {
        if(enters == 4) {
            content[t] = buffer[i];
            t++;
        }else {
            if (buffer[i] == '\n' || buffer[i] == '\r') {
                enters++;
            }
            else {
                enters = 0;
            }
        }
    }
    content[t] = '\0';
    //printf("\nContent size: %d, Content: %s \n", t, content);
    isReceiving = false;
    return content;
}

int getTimeZone()
{
    char* content = httpGet("/gettimezone.php");
    int timezone = atoi(content);
    free(content);
    printf("%d", timezone);
    return timezone;
}

void parseAlarmJson(char* content){
    int r;
    int i;
    jsmn_parser p;
    jsmntok_t token[100]; /* We expect no more than 128 tokens */

    jsmn_init(&p);
    r = jsmn_parse(&p, content, strlen(content), token, sizeof(token)/sizeof(token[0]));
    if (r < 0) {
        printf("Failed to parse JSON: %d \n", r);
    }else{
        printf("Aantal tokens found: %d \n\n", r);
    }



    int start = 1;
    int usedAlarms[maxAlarms()];
    int j;
    for(j = 0; j < maxAlarms(); j++){
        usedAlarms[j] = 0;
    }
    for(i = 1; i < r; i++)
    {
        struct _tm time = GetRTCTime();
        u_short port;
        char url[24];
        char ip[24];
        char name[16];
        int id;
        for (i = i; !((i + start) % 23 == 0); i++) {
            if (jsoneq(content, &token[i], "YYYY") == 0) {
                time.tm_year= getIntegerToken(content, &token[i + 1]) - 1900;
                i++;
            }else if (jsoneq(content, &token[i], "MM") == 0) {
                time.tm_mon=  getIntegerToken(content, &token[i + 1]) - 1;
                i++;
            }else if (jsoneq(content, &token[i], "DD") == 0) {
                time.tm_mday =  getIntegerToken(content, &token[i + 1]);
                i++;
            }else if (jsoneq(content, &token[i], "hh") == 0) {
                time.tm_hour = 	getIntegerToken(content, &token[i + 1]);
                i++;
            }else if (jsoneq(content, &token[i], "mm") == 0) {
                time.tm_min = getIntegerToken(content, &token[i + 1]);
                i++;
            }else if (jsoneq(content, &token[i], "ss") == 0) {
                time.tm_sec = getIntegerToken(content, &token[i + 1]);
                i++;
            }else if (jsoneq(content, &token[i], "id") == 0) {
                id = getIntegerToken(content, &token[i + 1]);
                i++;
            }else if (jsoneq(content, &token[i], "port") == 0) {
                port = getIntegerToken(content, &token[i + 1]);
                i++;
            }else if (jsoneq(content, &token[i], "ip") == 0) {
                getStringToken(content, &token[i + 1], ip);
                i++;
            }else if (jsoneq(content, &token[i], "url") == 0) {
                getStringToken(content, &token[i + 1], url);
                i++;
            }else if (jsoneq(content, &token[i], "name") == 0) {
                getStringToken(name, &token[i + 1], name);
                i++;
            }
        }
        start = 0;

        int idx = alarmExist(id);
        if(idx == -1){
            printf("New alarm found!\n");
            printf("Alarm time is: %02d:%02d:%02d\n", time.tm_hour, time.tm_min, time.tm_sec);
            printf("Alarm date is: %02d.%02d.%02d\n", time.tm_mday, (time.tm_mon + 1), (time.tm_year + 1900));
            printf("Alarm stream data is: %s:%d%s\n", ip, port, url);
            printf("Alarm id and name is: %d %s\n\n", id, name);

            //zoek naar een vrije plaats in de alarm array
            for(j = 0; j < maxAlarms(); j++){
                if(usedAlarms[j] == 0){ //Dit is een lege plaats, hier kunnen we ons nieuwe alarm plaatsen
                    setAlarm(time, name, ip, port, url, 5, id, j);
                    usedAlarms[j] = 1;
                    j = 10;
                }
            }
        }else{
            usedAlarms[idx] = 1; //Alarm bestaat al, dus we houden deze plaats vrij voor dat alarm
        }
        NutDelay(1000);
    }
    for(j = 0; j < maxAlarms(); j++){ //Alle overige plaatsen, die wij niet gezet hebben, verwijderen.
        if(usedAlarms[j] == 0){
            deleteAlarm(j);
        };
    }
}

bool NetworkIsReceiving(void){
    return isReceiving;
}

bool hasNetworkConnection(void){
    return hasNetwork;
}