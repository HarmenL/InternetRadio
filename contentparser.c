//
// Created by janco on 25-3-16.
//
#include "contentparser.h"
#include "ntp.h"
#include "network.h"
#include "jsmn.h"
#include "rtc.h"
#include "alarm.h"
#include "vs10xx.h"
#include "httpstream.h"

void parseAlarmJson(char* content){
    int r;
    int i;
    jsmn_parser p;
    jsmntok_t token[150]; /* We expect no more than 128 tokens */

    jsmn_init(&p);
    r = jsmn_parse(&p, content, strlen(content), token, sizeof(token)/sizeof(token[0]));
    if (r <= 0) {
        printf("Failed to parse JSON: %d \n", r);
        return;
    }else{
        printf("Aantal tokens found: %d \n", r);
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
        char st;
        memset(url, 0, 24);
        memset(ip, 0, 24);
        memset(name, 0, 16);

        int id;
        for (i = i; !((i + start) % 26 == 0); i++) {
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
                getStringToken(content, &token[i + 1], name);
                i++;
            }else if (jsoneq(content, &token[i], "st") == 0) {
                st = getIntegerToken(content, &token[i + 1]);
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
            printf("Alarm id and name and st is: %d %s %d\n\n", id, name, st);

            //zoek naar een vrije plaats in de alarm array
            for(j = 0; j < maxAlarms(); j++){
                if(usedAlarms[j] == 0){ //Dit is een lege plaats, hier kunnen we ons nieuwe alarm plaatsen
                    setAlarm(time, name, ip, port, url, st, id, j);
                    usedAlarms[j] = 1;
                    j = 10;
                }
            }
        }else{
            usedAlarms[idx] = 1; //Alarm bestaat al, dus we houden deze plaats vrij voor dat alarm
        }
    }
    for(j = 0; j < maxAlarms(); j++){ //Alle overige plaatsen, die wij niet gezet hebben, verwijderen.
        if(usedAlarms[j] == 0){
            deleteAlarm(j);
        };
    }
}

void parseCommandQue(char* content){
    int r;
    int i;
    jsmn_parser p;
    jsmntok_t token[150]; /* We expect no more than 128 tokens */

    jsmn_init(&p);
    r = jsmn_parse(&p, content, strlen(content), token, sizeof(token)/sizeof(token[0]));
    if (r <= 0) {
        printf("Failed to parse JSON: %d \n", r);
        return;
    }else{
        printf("Aantal tokens found: %d \n", r);
    }

    for(i = 0; i < r; i++)
    {
        if (jsoneq(content, &token[i], "command") == 0) {
            if(jsoneq(content, &token[i + 1], "volume") == 0){
                char vol = getIntegerToken(content, &token[i + 3]);
                vol = 128 - ((vol * 128) / 100);
                VsSetVolume(vol, vol);
                i += 3;
            }else if(jsoneq(content, &token[i + 1], "stopstream") == 0){
                stopStream();
                i += 3;
            }else if(jsoneq(content, &token[i + 1], "startstream") == 0){
                u_short port = getIntegerToken(content, &token[i + 9]);
                char url[24];
                char ip[24];
                getStringToken(content, &token[i + 7], url);
                getStringToken(content, &token[i + 5], ip);
                playStream(ip, port, url);
                i += 9;
            }
        }
    }
}

void parsetimezone(char* content)
{
    int timezone = atoi(content);
    setTimeZone(timezone);
    printf("%d", timezone);
}
