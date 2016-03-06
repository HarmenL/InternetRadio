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
#include "alarm.h"

void NetworkInit() {
    /* Register de internet controller. */
    if (NutRegisterDevice(&DEV_ETHER, 0, 0)) {
        printf("Registering  failed.");
    }/* Netwerk configureren op dhcp */
    else if (NutDhcpIfConfig(DEV_ETHER_NAME, NULL, 0)) {
        /* Done. */
    }else {
        printf("Ik heb een internet connectie. Ip is: %s \n\n", inet_ntoa(confnet.cdn_ip_addr));
    }
}

char* httpGet(char address[]){
    NutDelay(1000);
    TCPSOCKET* sock = NutTcpCreateSocket();
    char http[150];
    sprintf(http, "GET %s HTTP/1.1\r\nHost: saltyradio.jancokock.me \r\n\r\n", address);
    NutDelay(100);
    char buffer[300];
    int len = sizeof(http);
    if (NutTcpConnect(sock, inet_addr("62.195.226.247"), 80)) {
        printf("Can't connect to server\n");
    }else{
        //FILE *stream;
        //stream = _fdopen((int) sock, "r b");
        if(NutTcpSend(sock, http, len) != len){
            printf("Writing headers failed.");
            NutDelay(1000);
        }else{
            printf("Headers %s writed. Now reading.", http);
            NutDelay(1000);
            NutTcpReceive(sock, buffer, sizeof(buffer));
            //fread(buffer, 1, sizeof(buffer), stream);
            NutDelay(1000);
            printf(buffer);
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

    struct _tm time = GetRTCTime();

    for (i = 1; i < r; i++) {
        if (jsoneq(content, &token[i], "YYYY") == 0) {
            /* We may use strndup() to fetch string value */
            char yyyy[4];
            sprintf(yyyy, "%.*s", token[i+1].end-token[i+1].start, content + token[i+1].start);
            printf("Tijd jaren: %s\n", yyyy);
            time.tm_year = atoi(yyyy) - 1900;    //only use when 100% sure input is an integer
            i++;
        }else if (jsoneq(content, &token[i], "MM") == 0) {
            char mm[2];
            sprintf(mm, "%.*s", token[i+1].end-token[i+1].start, content + token[i+1].start);
            printf("Tijd maand: %s\n", mm);
            time.tm_mon= atoi(mm) - 1;    //only use when 100% sure input is an integer
            i++;
        }else if (jsoneq(content, &token[i], "DD") == 0) {
            char dd[2];
            sprintf(dd, "%.*s", token[i + 1].end - token[i + 1].start, content + token[i + 1].start);
            printf("Tijd dagen: %s\n", dd);
            time.tm_mday = atoi(dd);     //only use when 100% sure input is an integer
            i++;
        }else if (jsoneq(content, &token[i], "hh") == 0) {
            char hh[2];
            sprintf(hh, "%.*s", token[i+1].end-token[i+1].start, content + token[i+1].start);
            printf("Tijd uren: %s\n", hh);
            time.tm_hour = atoi(hh);    //only use when 100% sure input is an integer
            i++;
        }else if (jsoneq(content, &token[i], "mm") == 0) {
            char mm[2];
            sprintf(mm, "%.*s", token[i+1].end-token[i+1].start, content + token[i+1].start);
            printf("Tijd minuten: %s\n", mm);
            time.tm_min = atoi(mm);    //only use when 100% sure input is an integer
            i++;
        }else if (jsoneq(content, &token[i], "ss") == 0) {
            char ss[2];
            sprintf(ss, "%.*s", token[i + 1].end - token[i + 1].start, content + token[i + 1].start);
            printf("Tijd seconden: %s\n", ss);
            time.tm_sec = atoi(ss);     //only use when 100% sure input is an integer
            i++;
        }
    }
   // printf("alarmtime %02d-%02d-%04d || %02d-%02d-%02d", time.tm_mday, time.tm_mon+1, time.tm_year+1900, time.tm_hour, time.tm_min, time.tm_sec);
   // setAlarm(time, "none", 0);
    struct _tm alarmtime = GetRTCTime();
    alarmtime.tm_sec = alarmtime.tm_sec+10;

    X12RtcSetAlarm(0,&time,0b11111111);
    NutDelay(1000);
}