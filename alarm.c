#define LOG_MODULE  LOG_MAIN_MODULE

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "log.h"
#include "rtc.h"
#include "alarm.h"

struct _alarm{
	int seconds;
	char name[16];
};

void setAlarm(struct _tm time, char *name, int sec){
	struct _alarm al;
	
	X12RtcSetAlarm(0, &time, AFLGS);
	NutDelay(100);
	
	al.seconds = sec;
	strncpy(al.name, name, sizeof(al.name));
	
	//Schrijf struct naar eeprom
}

int getDuration(){
	//Haal duration op uit eeprom
	return 10;
}

char* getName(){
	//haal naam op uit eeprom en geef de pointer mee
	char str[17];
	//int x = 561;
	//sprintf(str,"test123456789%d", x);
	sprintf(str, "     Wekker     ");
	return str;
}

void handleAlarm(){
	struct _tm alarmtime;
	
    alarmtime = GetRTCTime();
	
    X12RtcGetAlarm(0,&alarmtime,AFLGS);
	alarmtime.tm_min = (alarmtime.tm_min-79);
	alarmtime.tm_mday = (alarmtime.tm_mday - 80);
	alarmtime.tm_mon = (alarmtime.tm_mon - 80);
	
		
	X12RtcSetAlarm(0,&alarmtime, AFLGS);
	NutDelay(100);
	X12RtcClearStatus(ALARM_1);
}

int checkTime(){
	/*struct _tm ctime;
	struct _tm atime;
	time_t at;
	time_t ct;
	time_t diff;
	
	atime = GetRTCTime();
	ctime = GetRTCTime();
	
	X12RtcGetAlarm(0,&atime,0b11111111);
	atime.tm_min = atime.tm_min - 80;
	atime.tm_mday = (atime.tm_mday - 80);
	atime.tm_mon = (atime.tm_mon - 80);
	atime.tm_year = 116;
	
	LogMsg_P(LOG_INFO, PSTR("at %02d-%02d-%04d || %02d-%02d-%02d"), atime.tm_mday, atime.tm_mon+1, atime.tm_year+1900, atime.tm_hour, atime.tm_min, atime.tm_sec);
	
	ct = mktime(&ctime);
	at = mktime(&atime);
	
	at += getDuration();
	
	LogMsg_P(LOG_INFO, PSTR("at = %d, ct = %d"), at, ct);
	
	diff = ct - at;
	
	if (diff > 0){
		return 1;
	}*/
	return 0;
}

