#define LOG_MODULE  LOG_MAIN_MODULE

/*--------------------------------------------------------------------------*/
/*  Include files                                                           */
/*--------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include <sys/thread.h>
#include <sys/timer.h>
#include <sys/version.h>
#include <dev/irqreg.h>
#include <time.h>

/*--------------------------------------------------------------------------*/
/*  Stream-IT Lib files                                                     */
/*--------------------------------------------------------------------------*/
#include "lib/led.h"
#include "lib/system.h"
#include "lib/portio.h"
#include "lib/display.h"
#include "lib/remcon.h"
#include "lib/keyboard.h"
#include "lib/log.h"
#include "lib/uart0driver.h"
#include "lib/mmc.h"
//#include "lib/watchdog.h"
#include "lib/flash.h"
#include "lib/spidrv.h"
#include "lib/rtc.h"


int main(void)
{
    LedInit();
    Uart0DriverInit();
    Uart0DriverStart();
    LogInit();
    LogMsg_P(LOG_INFO, PSTR("Hello World"));
    LcdBackLight(LCD_BACKLIGHT_ON);

    for (;;)
    {
        LedControl(LED_TOGGLE);
        NutSleep(1000);
    }
    return(0);
}
