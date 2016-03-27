/*
 *  Copyright 20152016-TI2.3A6, 2016.
 *
 *  Project             : 20152016-TI2.3a6-Internet Radio
 *  Module              : NTP
 *  File name           : ntp.c
 *  Revision            : 1.1
 *  Creation Date       : 2016
 *
 *  Description         : This module syncs the time from a network time
 *                        server using the NTP-protocol.
 */

#include <dev/board.h>
#include <dev/debug.h>
#include <dev/nvmem.h>

#include <sys/timer.h>

#include <arpa/inet.h>
#include <net/route.h>
#include <pro/dhcp.h>
#include <pro/sntp.h>

#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <time.h>

#include "eeprom.h"
#include "log.h"
#include "ntp.h"

#define LOG_MODULE  LOG_NTP_MODULE

extern bool isSyncing = false;
extern bool validTime = false;
time_t ntp_time = 0;
tm *ntp_datetime;
int TIME_ZONE = 1;

void NtpInit(void) {
    puts("Func: NtpInit(void)");
    /* Timezone van nederland (gmt 1) */
    _timezone = -TIME_ZONE * 3600;
    NtpCheckValidTime();
}

bool NtpIsSyncing(void){
    return isSyncing;
}

void NtpCheckValidTime(void){
    puts("Func: NtpCheckValidTime(void)");
    TCache *cache;

    if (EepromGetCache(cache) == false){
        puts("NtpCheckValidTime(): No cache available");
        validTime = false;
        return;
    }

    // Cache is present
    puts("NtpCheckValidTime(): Cache is available");

    // Check time is valid;
    tm current_tm;
    X12RtcGetClock(&current_tm);

    tm stored_tm = cache->last_sync;

    validTime = NtpCompareTime(current_tm, stored_tm);
    if (validTime){
        puts("NtpCheckValidTime(): Time was valid \n");
    }else {
        puts("NtpCheckValidTime(): Invalid time! \n");
    }
}

//Tests if t1 is after t2.
bool NtpCompareTime(tm t1, tm t2){

    if (t1.tm_year > t2.tm_year){
        return true;
    }
    if (t1.tm_year == t2.tm_year && t1.tm_mon > t2.tm_mon){
        return true;
    }
    if (t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon && t1.tm_mday > t2.tm_mday){
        return true;
    }
    if (t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon && t1.tm_mday == t2.tm_mday && t1.tm_hour > t2.tm_hour){
        return true;
    }
    if (t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon && t1.tm_mday == t2.tm_mday && t1.tm_hour == t2.tm_hour && t1.tm_min > t2.tm_min){
        return true;
    }
    if (t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon && t1.tm_mday == t2.tm_mday && t1.tm_hour == t2.tm_hour && t1.tm_min == t2.tm_min &&t1.tm_sec > t2.tm_sec){
        return true;
    }

    return false;
}

bool NtpTimeIsValid(void){
    return validTime;
}

void NtpSync(void){
    /* Ophalen van pool.ntp.org */
    isSyncing = true;
    httpGet("/gettimezone.php", parsetimezone);
    printf(TIME_ZONE);
    NutDelay(100);
    puts("Tijd ophalen van pool.ntp.org (213.154.229.24)");
    uint32_t timeserver = inet_addr("213.154.229.24");

    for (;;) {
        if (NutSNTPGetTime(&timeserver, &ntp_time) == 0) {
            break;
        } else {
            puts("Fout bij het ontvangen van de tijd");
            NutSleep(1000);
        }
    }

    ntp_datetime = localtime(&ntp_time);

    printf("NTP time is: %02d:%02d:%02d\n", ntp_datetime->tm_hour, ntp_datetime->tm_min, ntp_datetime->tm_sec);
    printf("NTP date is: %02d.%02d.%02d\n\n", ntp_datetime->tm_mday, (ntp_datetime->tm_mon + 1), (ntp_datetime->tm_year + 1900));

    X12RtcSetClock(ntp_datetime);
    NtpWriteTimeToEeprom(*ntp_datetime);

    isSyncing = false;
    validTime = true;

    NutSleep(100);
}

void NtpWriteTimeToEeprom(tm time_struct){
    TCache cache;

    cache.last_sync = time_struct;
    EepromSetCache(&cache);
}

//unsigned long TmStructToEpoch(tm tm_struct){
//
//}
