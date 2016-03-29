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

struct _fallSleep
{
	struct _tm sleepTime;
};
struct _tm count;
void setSleep()
{
	X12RtcGetClock(&count);
	fallSleep.sleepTime = count;
	fallSleep.sleepTime.tm_hour += 1;
	playStream("62.195.226.247",80,"/test.mp3");
	return 1;
}
void checkSleep()
{
	X12RtcGetClock(&count);
	if(compareTime(count, fallSleep.sleepTime) >= 4){
		stopStream();
	}
	return 1;
}
