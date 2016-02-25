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

#include "ntp.h"

time_t ntp_time = 0;
tm *ntp_datetime;
uint32_t timeserver = 0;

void NtpInit() {
    /* Timezone van nederland (gmt 1) */
    _timezone = -2 * 60 * 60;
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

    NutRtcSetTime(ntp_datetime);


    // This isn't working...
    tm *test;

    X12RtcGetClock(test);

    printf("RTC time is: %02d:%02d:%02d\n", test->tm_hour, test->tm_min, test->tm_sec);
    printf("RTC date is: %02d.%02d.%02d\n\n", test->tm_mday, (test->tm_mon + 1), (test->tm_year + 1900));
}

