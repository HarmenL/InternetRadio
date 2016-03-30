//
// Created by Jordy Sipkema on 26/02/16.
//
#define LOG_MODULE  LOG_MAIN_MODULE

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "display.h"
#include "displayHandler.h"
#include "ntp.h"
#include "log.h"
#include "rtc.h"
#include "alarm.h"
#include "network.h"

#define MONTH_OFFSET 1
#define YEAR_OFFSET 1900

bool displayingCustomMessage = false;

void (*write_display_ptr[2])(char*, int) = {LcdArrayLineOne, LcdArrayLineTwo};

void displayTime(int line_number){
    tm time;
    X12RtcGetClock(&time);

    char str[16];
    if (1){
        sprintf(str, "    %02d:%02d:%02d    ", time.tm_hour, time.tm_min, time.tm_sec);
    }else {
        sprintf(str, "    ??:??:??    ");
    }

    if (line_number > -1 && line_number < 2){
        (*write_display_ptr[line_number])(str, 16);
    }
}

void displayDate(int line_number) {
    tm *time;
    X12RtcGetClock(time);

    char str[16];

    if (1) {
        sprintf(str, "   %02d-%02d-%04d      ", time->tm_mday, time->tm_mon + MONTH_OFFSET, time->tm_year + YEAR_OFFSET);
    } else {
        sprintf(str, "   ??-??-????      ");
    }

    if (NtpIsSyncing()) {
       str[1] = 'S';
    }else if(NetworkIsReceiving()){
        str[1] = 'N';
    }

    if (line_number > -1 && line_number < 2){
        (*write_display_ptr[line_number])(str, 16);
    }
}

void displayAlarm(int line_number, int line_numberTwo, int idx)
{
	int i;
	int j;
	int startidx;
    char str[16];
	struct _alarm am = getAlarm(idx);

    sprintf(str, "    %02d:%02d:%02d    ", am.time.tm_hour, am.time.tm_min, am.time.tm_sec);
    if (line_number > -1 && line_number < 2){
        (*write_display_ptr[line_number])(str, 16);
    }

	j = 0;
    char str2[16];
	for (i = 0; i < 16;i++){
		if (am.name[i] != 0){
			j = j + 1;
		}
	}

	if (j != 16){
		startidx = (8-(j/2));
	}
	j = 0;
	for(i = 0; i < 16; i++){
		if (i >= startidx){
			if (am.name[j] != 0){
				str2[i] = am.name[j];
			} else {
				str2[i] = ' ';
			}
			j++;
		} else {
			str2[i] = ' ';
		}
	}
    if (line_numberTwo > -1 && line_numberTwo < 2){
        (*write_display_ptr[line_numberTwo])(str2, 16);
        LcdBackLight(LCD_BACKLIGHT_ON);
    }


}

void displayVolume(int pos)
{
    ClearLcd();
    int i;
    LcdArrayLineOne("     Volume     ", 16);

    char characters[17];

    for(i = 0; i < 17; i++)
    {
        characters[i] = 0xFF;
    }
        LcdArrayLineTwo(characters,pos);
}

void displayTwitter(char* text)
{
    //int lineNumber,char text[]
    ClearLcd();
    displayingCustomMessage = true;
    LcdArrayLineOne("     Twitter    ", 16);
    int j = 0;
    int i;
    char text1[16];
    //char text2[140] = text;
    int shift = 0;
    //char *text = "Twitter";
    for(i = 0; i<200;i++){
        if (text[i] != 0){
            j++;
        }
    }

    while(1) {


        /*for (i = 0; i < 16; ++i) {
            LcdArrayLineOne(getLoop(text, shift + i), 7);
            shift++;
        }*/
        for(i = 0; i < 16; i++){
            if (text[shift+i]!= 0) {
                text1[i] = text[shift + i];
            } else {
                text1[i] = ' ';
            }
        }
        printf("%s\n", text1);
        LcdArrayLineTwo(text1,16);
        shift++;
        if (shift > j){
            shift = 0;
        }
        NutDelay(500);
    }
}


void displayTwitch(char name[], char title[], char game[])
{
    displayingCustomMessage = true;
    ClearLcd();
    LcdArrayLineOne(name, strlen(name));
    LcdArrayLineTwo("Streaming", 9);
    LcdBackLight(LCD_BACKLIGHT_ON);
}

bool isDisplayingCustomMessage(){
    return displayingCustomMessage;
}

void setDisplayingCustomMessage(bool value){
    displayingCustomMessage = value;
}
