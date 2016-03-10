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
        printf("Registering  failed. \n");
    }/* Netwerk configureren op dhcp */
    else if (NutDhcpIfConfig(DEV_ETHER_NAME, NULL, 0)) {
        printf("DHCP failed. \n");
    }else {
        printf("Ik heb een internet connectie. Ip is: %s \n\n", inet_ntoa(confnet.cdn_ip_addr));
    }
}

char* httpGet(char address[]){
    NutDelay(1000);
    printf("\n\n #-- HTTP get -- #\n");

    TCPSOCKET* sock = NutTcpCreateSocket();

    char http[strlen(address) + 49]; //49 chars based on get command. Change this number if you change the domain name
    sprintf(http, "GET %s HTTP/1.1\r\nHost: saltyradio.jancokock.me \r\n\r\n", address);
    int len = sizeof(http);

    char buffer[300];
    if (NutTcpConnect(sock, inet_addr("62.195.226.247"), 80)) {
        printf("Can't connect to server\n");
    }else{
        //FILE *stream;
        //stream = _fdopen((int) sock, "r b");
        if(NutTcpSend(sock, http, len) != len){
            printf("Writing headers failed.\n");
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
    printf("\nContent size: %d, Content: %s \n", t, content);
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
            char yyyy[4];
            sprintf(yyyy, "%.*s", token[i+1].end-token[i+1].start, content + token[i+1].start);
            printf("Tijd jaar: %s\n", yyyy);
            time.tm_mon= atoi(yyyy) - 1900;    //only use when 100% sure input is an integer
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
    X12RtcSetAlarm(0,&time,0b11111111);
    NutDelay(1000);
}