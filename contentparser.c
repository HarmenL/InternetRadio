//
// Created by janco on 25-3-16.
//
#include "contentparser.h"
#include "ntp.h"
#include "network.h"
#include "jsmn.h"
#include "rtc.h"
#include "alarm.h"
#include "displayHandler.h"

void parseAlarmJson(char* content){
    int r;
    int i = 2;
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

    int usedAlarms[maxAlarms()];
    int j;
    struct _tm time = GetRTCTime();
    for(j = 0; j < maxAlarms(); j++){
        usedAlarms[j] = 0;
    }
    for(i; i < r; i++)
    {
        int id;
        u_short port;
        char url[24];
        char ip[24];
        char name[16];
        char st = -1;
        memset(url, 0, 24);
        memset(ip, 0, 24);
        memset(name, 0, 17);

        for (i; (st == -1 && i < r); i+=2) {                                //Zodra ST is gevonden, betekent dit de laatste token van een alarm.
            if (jsoneq(content, &token[i], "YYYY") == 0) {
                time.tm_year= getIntegerToken(content, &token[i + 1]) - 1900;
            }else if (jsoneq(content, &token[i], "MM") == 0) {
                time.tm_mon=  getIntegerToken(content, &token[i + 1]) - 1;
            }else if (jsoneq(content, &token[i], "DD") == 0) {
                time.tm_mday =  getIntegerToken(content, &token[i + 1]);
            }else if (jsoneq(content, &token[i], "hh") == 0) {
                time.tm_hour = 	getIntegerToken(content, &token[i + 1]);
            }else if (jsoneq(content, &token[i], "mm") == 0) {
                time.tm_min = getIntegerToken(content, &token[i + 1]);
            }else if (jsoneq(content, &token[i], "ss") == 0) {
                time.tm_sec = getIntegerToken(content, &token[i + 1]);
            }else if (jsoneq(content, &token[i], "id") == 0) {
                id = getIntegerToken(content, &token[i + 1]);
            }else if (jsoneq(content, &token[i], "port") == 0) {
                port = getIntegerToken(content, &token[i + 1]);
            }else if (jsoneq(content, &token[i], "ip") == 0) {
                getStringToken(content, &token[i + 1], ip);
            }else if (jsoneq(content, &token[i], "url") == 0) {
                getStringToken(content, &token[i + 1], url);
            }else if (jsoneq(content, &token[i], "name") == 0) {
                getStringToken(content, &token[i + 1], name);
            }else if (jsoneq(content, &token[i], "st") == 0) {
                st = getIntegerToken(content, &token[i + 1]);
                i+=2;
            }
        }

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
                    j = 10;             //Uit de for loop
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

void parsetimezone(char* content)
{
    int timezone = atoi(content);
    printf("%d", timezone);
}

void parseTwitch(char* content)
{
    if(!strcmp("null", content))
    {
        printf("Nobody is streaming");
        return;
    }
    int r;
    int i = 1;
    jsmn_parser p;
    jsmntok_t token[20]; /* We expect no more than 20 tokens */

    jsmn_init(&p);
    r = jsmn_parse(&p, content, strlen(content), token, sizeof(token)/sizeof(token[0]));
    if (r <= 0) {
        printf("Failed to parse JSON: %d \n", r);
        return;
    }else{
        printf("Aantal tokens found: %d \n", r);
    }

    char name[20];
    char title[30];
    char game[20];

    for(i; i < r; i++)
    {
        if(jsoneq(content, &token[i], "Name"))
        {
            getStringToken(content, &token[i+1], name);
            printf("%s", name);
            i++;
        }
        else if(jsoneq(content, &token[i], "Title"))
        {
            getStringToken(content, &token[i+1], title);
            i++;
        }
        else if(jsoneq(content, &token[i], "Game"))
        {
            getStringToken(content, &token[i+1], game);
            i++;
        }
    }
    displayTwitch(name, title, game);
}
