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
#include "gotosleep.h"
struct _fallSleep
{
	struct _tm sleepTime;
};
struct _tm count;
int i = 0;
void setSleep()
{
	X12RtcGetClock(&count);
	fallSleep.sleepTime = count;
	fallSleep.sleepTime.tm_hour += 1;
	changeChanel();
	return 1;
}
void checkSleep(int vol1)
{
	X12RtcGetClock(&count);
	if(compareTime(count, fallSleep.sleepTime) == 0){
		stopStream();
		i = 0;
	}
	return 1;
}
void changeChanel(){
	
	if (i > 2){
		i =1;
	}
	switch(i) {
	case 0  :
      playStream("62.195.226.247",80,"/test.mp3");
	  i = 2;
      break;
   case 1  :
	  stopStream(); 
      playStream("62.195.226.247",80,"/test.mp3");
	  i++;
      break;
	
   case 2  :
      stopStream(); 
      playStream("62.195.226.247",80,"/test2.mp3");
	  i++;
      break;
}
return 1;
}
