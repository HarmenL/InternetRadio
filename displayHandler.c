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
#include "httpstream.h"

#define MONTH_OFFSET 1
#define YEAR_OFFSET 1900

void (*write_display_ptr[2])(char*, int) = {LcdArrayLineOne, LcdArrayLineTwo};

void displayTime(int line_number){
    tm time;
    X12RtcGetClock(&time);

    char str[16];
    if (NtpTimeIsValid()){
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

    if (NtpTimeIsValid()) {
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
    char str[12];
	struct _alarm am = getAlarm(idx);
    sprintf(str, "    %02d:%02d:%02d    ", am.time.tm_hour, am.time.tm_min, am.time.tm_sec);
    if (line_number > -1 && line_number < 2){
        (*write_display_ptr[line_number])(str, 12);
    }
    playStream(am.ip, am.port, am.url);

    char str2[16];
	for(i = 0; i < 17; i++){
		str2[i] = am.name[i];
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
    (*write_display_ptr[0])("     Volume     ", 16);

    char characters[17];

    for(i = 0; i < 17; i++)
    {
        characters[i] = 0xFF;
    }

    (*write_display_ptr[1])(characters, pos);
}



