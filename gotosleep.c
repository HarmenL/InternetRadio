#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/thread.h>
#include <sys/timer.h>
#include <sys/version.h>
#include <dev/irqreg.h>
#include "log.h"
#include "rtc.h"
#include "alarm.h"
#include "display.h"
#include "httpstream.h"
#include "mp3stream.h"
#include "gotosleep.h"
struct _fallSleep
{
	struct _tm sleepTime;
};
struct _tm count;
int i = 1;
int x = 0;
void setSleep(void)
{
	X12RtcGetClock(&count);
	fallSleep.sleepTime = count;
	AddMinutes(60);
	
	changeChanel();
	x = fallSleep.sleepTime.tm_min;
	
	return 1;
}
void AddMinutes(int minutes){
	if (fallSleep.sleepTime.tm_min + minutes >= 60){ //Checks if minutes is >= 60 else minute
		fallSleep.sleepTime.tm_hour += 1;
		fallSleep.sleepTime.tm_min = ((snooze[idx].snoozeTime.tm_min + minutes) % 60);
		if (fallSleep.sleepTime.tm_hour >= 24){ //Checks if hours is >= 24
			fallSleep.sleepTime.tm_hour = 0;
			if ((fallSleep.sleepTime.tm_mday + 1) <= daysInMonth((fallSleep.sleepTime..tm_mon+1), (fallSleep.sleepTime.tm_year+1900))){ //Checks if day+1 smaller or even is to the amount of days in the month
				fallSleep.sleepTime.tm_mday += 1;
			} else { //If the days+1 is bigger than the amount of days in the month, day = 1 & month is + 1
				fallSleep.sleepTime.tm_mday = 1;
				if (fallSleep.sleepTime.tm_mon + 1 > 11){//If month+1 is bigger than 11 (month is 0-11) then month = 0 & year + 1
					fallSleep.sleepTime.tm_mon = 0;
					fallSleep.sleepTime.tm_year += 1;
				} else {
					fallSleep.sleepTime.tm_mon += 1;
				}
			}
		}
	} else {
		fallSleep.sleepTime.tm_min += minutes;
	}
}
void checkSleep(void)
{
	X12RtcGetClock(&count);
	if(compareTime(count, fallSleep.sleepTime) == 0){
		killPlayerThread(); 
	}
	if(compareTime(count, fallSleep.sleepTime) == 5 && fallSleep.sleepTime.tm_min == x){
		volumeDown();
		if (x >= 60){
			x = 0;
		}
		x += 2;
	}
	return 1;
}
void changeChanel(void){
	
	if (i > 2){
		i =1;
	}
	switch(i) {
   case 1  :
	  killPlayerThread(); 
      connectToStream("62.195.226.247",80,"/test.mp3");
	  play();
	  i++;
      break;
	
   case 2  :
	  killPlayerThread(); 
      connectToStream("62.195.226.247",80,"/test2.mp3");
	  play()
	  i++;
      break;
}
return 1;
}
