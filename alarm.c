#define LOG_MODULE  LOG_MAIN_MODULE

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "log.h"
#include "rtc.h"
#include "alarm.h"

#define n 5


struct _snooze
{
	struct _tm snoozeStart;
	struct _tm snoozeEnd;
};

struct _alarm alarm[n];
struct _snooze snooze[n];


int checkAlarms(){
	int i = 0;
	int check = 0;
	for (i = 0; i < n; i++){
		setState(i);
		if (alarm[i].state == 1){
			check = 1;
		}
	}
	if (check == 1){
		return 1;
	}
	
	return 0;
}

int alarmExist(int id){
	int g;
	for (g = 0; g < n; g++){
		if (alarm[g].id == id){
			return g;
		}
	}
	return -1;
}

struct _alarm getAlarm(int idx){
	return alarm[idx];
}

int getState(int idx){
	return alarm[idx].state;
}

int maxAlarms(){
	return n;
}

void setState(int idx){
	struct _tm ct;
	X12RtcGetClock(&ct);
	
	if (compareTime(ct, alarm[idx].time) == 1 && alarm[idx].time.tm_year != 0){
		alarm[idx].state = 1;
	} else {
		alarm[idx].state = 0;
	}
	
	/*if (compareTime(alarm[idx].time,snooze[idx].snoozeStart)){
		alarm[idx].state = 2;
	}
	
	if (alarm[idx].state == 2){
		if (compareTime(alarm[idx].time, snooze[idx].snoozeEnd)){
			snooze[idx].snoozeStart.tm_min += alarm[idx].snooze + 1;
			snooze[idx].snoozeEnd.tm_min += alarm[idx].snooze + 1;
		}
	}*/
}

/*void getAlarm(struct _alarm *am){
	int i = 0;
	for (i = 0; i < n; i++){
		am[i] = alarm[i]; 
	}
}*/

void setAlarm(struct _tm time, char* name, char* ip, u_short port, char* url, int snooze, int id, int idx){
	alarm[idx].time = time;
	
	strncpy(alarm[idx].name, name, sizeof(alarm[idx].name));
	strncpy(alarm[idx].ip, ip, sizeof(alarm[idx].ip));
	alarm[idx].port = port;
	strncpy(alarm[idx].url, url, sizeof(alarm[idx].url));

	alarm[idx].snooze = snooze;
	alarm[idx].id = id;
	alarm[idx].state = 0;

	//snooze[idx].snoozeStart = time;
	//snooze[idx].snoozeEnd = time;
	//snooze[idx].snoozeStart += 1;
	//snooze[idx].snoozeEnd += (snooze +1);
}


void deleteAlarm(int idx){
	struct _tm tm;
	tm.tm_year = 0;
	alarm[idx].time = tm;
	alarm[idx].port = 0;
	alarm[idx].snooze = 5;
	alarm[idx].id = -1;
	alarm[idx].state = -1;
}

void handleAlarm(int idx){
	alarm[idx].time.tm_mday = alarm[idx].time.tm_mday + 1;
	alarm[idx].state = 0;
}

int compareTime(tm t1,tm t2){
    if (t1.tm_year > t2.tm_year){
        return 1;
	}
    if (t1.tm_year == t2.tm_year && t1.tm_mon > t2.tm_mon){
        return 1;
	}
    if (t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon && t1.tm_mday > t2.tm_mday){
        return 1;
	}
    if (t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon && t1.tm_mday == t2.tm_mday && t1.tm_hour > t2.tm_hour){
        return 1;
	}
    if (t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon && t1.tm_mday == t2.tm_mday && t1.tm_hour == t2.tm_hour && t1.tm_min > t2.tm_min){
        return 1;
	}
    if (t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon && t1.tm_mday == t2.tm_mday && t1.tm_hour == t2.tm_hour && t1.tm_min == t2.tm_min &&t1.tm_sec > t2.tm_sec){
        return 1;
	}

    return 0;
}

