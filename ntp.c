//
// Created by janco on 25-2-16.
//
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

#include "log.h"
#include "ntp.h"
#include "eeprom.h"
#include "typedefs.h"

int TIME_ZONE = 1;
#define LOG_MODULE  LOG_NTP_MODULE

bool isSyncing;
bool validTime = false;
time_t ntp_time = 0;
tm *ntp_datetime;
uint32_t timeserver = 0;

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

    validTime = NtpCompareTime(current_tm, stored_tm);
    if (validTime){
        puts("NtpCheckValidTime(): Time was valid \n");
    }else {
        puts("NtpCheckValidTime(): Invalid time! \n");
    }

//    Eeprom_tm eeprom_tm_struct;
//
//    NutNvMemLoad(256, &eeprom_tm_struct, sizeof(eeprom_tm_struct));
//
//    if (eeprom_tm_struct.len != sizeof(eeprom_tm_struct)){
//        // Size mismatch: There is no valid configuration present.
//        puts("NtpCheckValidTime(): Size mismatch");
//        validTime = false;
//        return;
//    }
//
//    // Valid configuration available.
//    puts("NtpCheckValidTime(): Valid config available");
//    tm stored_tm = eeprom_tm_struct.tm_struct;
//
//    // Check time is valid;
//    tm current_tm;
//    X12RtcGetClock(&current_tm);
//
//    validTime = NtpCompareTime(current_tm, stored_tm);
//    if (validTime){
//        puts("NtpCheckValidTime(): Time was valid");
//    }else {
//        puts("NtpCheckValidTime(): Invalid time!");
//    }
}

//Tests if t1 is after t2.
bool NtpCompareTime(tm t1, tm t2){
    char debug[120];
    sprintf(&debug, "Comparing two times\nt1=%04d-%02d-%02d+%02d:%02d:%02d\nt2=%04d-%02d-%02d+%02d:%02d:%02d \n",
            t1.tm_year+1900,
            t1.tm_mon+1,
            t1.tm_mday,
            t1.tm_hour,
            t1.tm_min,
            t1.tm_sec,

            t2.tm_year+1900,
            t2.tm_mon+1,
            t2.tm_mday,
            t2.tm_hour,
            t2.tm_min,
            t2.tm_sec
    );
    puts(debug);

    if (t1.tm_year > t2.tm_year)
        return true;
    if (t1.tm_mon > t2.tm_mon)
        return true;
    if (t1.tm_mday > t2.tm_mday)
        return true;
    if (t1.tm_hour > t2.tm_hour)
        return true;
    if (t1.tm_min > t2.tm_min)
        return true;
    if (t1.tm_sec > t2.tm_sec)
        return true;

    //else
    return false;
}

bool NtpTimeIsValid(void){
    return validTime;
}

void NtpSync(void){
    /* Ophalen van pool.ntp.org */
    isSyncing = true;
    _timezone = -getTimeZone() * 3600;
    puts("NtpSync(): Timezone fetched. ");
    printf(TIME_ZONE);
    NutDelay(100);
    //puts("Tijd ophalen van pool.ntp.org (213.154.229.24)");
    timeserver = inet_addr("213.154.229.24");

    for (;;) {
        if (NutSNTPGetTime(&timeserver, &ntp_time) == 0) {
            break;
        } else {
            NutSleep(400);
            puts("Fout bij het ontvangen van de tijd");
        }
    }
    //puts("Opgehaald.\n");

    ntp_datetime = localtime(&ntp_time);

    printf("NTP time is: %02d:%02d:%02d\n", ntp_datetime->tm_hour, ntp_datetime->tm_min, ntp_datetime->tm_sec);
    printf("NTP date is: %02d.%02d.%02d\n\n", ntp_datetime->tm_mday, (ntp_datetime->tm_mon + 1), (ntp_datetime->tm_year + 1900));

    X12RtcSetClock(ntp_datetime);
    NtpWriteTimeToEeprom(*ntp_datetime);

    isSyncing = false;
    validTime = true;
}

void NtpWriteTimeToEeprom(tm time_struct){
    TCache cache;

    cache.last_sync = time_struct;
    EepromSetCache(&cache);
}

