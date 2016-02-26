//
// Created by janco on 25-2-16.
//
#include <dev/board.h>
#include <dev/debug.h>

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

#define TIME_ZONE 1
#define LOG_MODULE  LOG_NTP_MODULE

time_t ntp_time = 0;
tm *ntp_datetime;
uint32_t timeserver = 0;

void NtpInit() {
    /* Timezone van nederland (gmt 1) */
    _timezone = -TIME_ZONE * 3600;
    GetTime();
}

void GetTime(){
    /* Ophalen van pool.ntp.org */
    puts("Tijd ophalen van pool.ntp.org (213.154.229.24)");
    timeserver = inet_addr("213.154.229.24");

    for (;;) {
        if (NutSNTPGetTime(&timeserver, &ntp_time) == 0) {
            break;
        } else {
            NutSleep(400);
            puts("Fout bij het ontvangen van de tijd");
        }
    }
    puts("Opgehaald.\n");

    ntp_datetime = localtime(&ntp_time);

    printf("NTP time is: %02d:%02d:%02d\n", ntp_datetime->tm_hour, ntp_datetime->tm_min, ntp_datetime->tm_sec);
    printf("NTP date is: %02d.%02d.%02d\n\n", ntp_datetime->tm_mday, (ntp_datetime->tm_mon + 1), (ntp_datetime->tm_year + 1900));

    X12RtcSetClock(ntp_datetime);


    NutDelay(100);


    // for logging purposes
    tm gmt;
    X12RtcGetClock(&gmt);
    LogMsg_P(LOG_INFO, PSTR("RTC time [%02d:%02d:%02d]"), gmt.tm_hour, gmt.tm_min, gmt.tm_sec );
}
