//
// Created by Jordy Sipkema on 26/02/16.
//

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "display.h"
#include "displayHandler.h"
#include "rtc.h"

#define MONTH_OFFSET 1
#define YEAR_OFFSET 1900

void (*write_display_ptr[2])(char*, int) = {LcdArrayLineOne, LcdArrayLineTwo};

void displayTime(int line_number){
    tm time;
    X12RtcGetClock(&time);

    char str[12];
    sprintf(str, "    %02d:%02d:%02d", time.tm_hour, time.tm_min, time.tm_sec);

    if (line_number > -1 && line_number < 2){
        (*write_display_ptr[line_number])(str, 12);
    }
}

void displayDate(int line_number){
    tm *time;
    X12RtcGetClock(time);

    char str[13];
    sprintf(str, "   %02d-%02d-%04d", time->tm_mday, time->tm_mon+MONTH_OFFSET, time->tm_year+YEAR_OFFSET);

    if (line_number > -1 && line_number < 2){
        (*write_display_ptr[line_number])(str, 13);
    }
}



