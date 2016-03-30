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
	fallSleep.sleepTime.tm_hour += 1;
	changeChanel();
	x = fallSleep.sleepTime.tm_min;
	
	return 1;
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
