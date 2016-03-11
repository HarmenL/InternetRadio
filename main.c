/*! \mainpage SIR firmware documentation
 *
 *  \section intro Introduction
 *  A collection of HTML-files has been generated using the documentation in the sourcefiles to
 *  allow the developer to browse through the technical documentation of this project.
 *  \par
 *  \note these HTML files are automatically generated (using DoxyGen) and all modifications in the
 *  documentation should be done via the sourcefiles.
 */

/*! \file
 *  COPYRIGHT (C) SaltyRadio 2016
 *  \date 20-02-2016
 */

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

#include "displayHandler.h"
#include "system.h"
#include "portio.h"
#include "display.h"
#include "remcon.h"
#include "keyboard.h"
#include "led.h"
#include "log.h"
#include "uart0driver.h"
#include "mmc.h"
#include "watchdog.h"
#include "flash.h"
#include "spidrv.h"
#include "network.h"

#include <time.h>
#include "rtc.h"
#include "alarm.h"
#include "ntp.h"

/*-------------------------------------------------------------------------*/
/* local routines (prototyping)                                            */
/*-------------------------------------------------------------------------*/
static void SysMainBeatInterrupt(void*);
static void SysControlMainBeat(u_char);

/*-------------------------------------------------------------------------*/
/* Stack check variables placed in .noinit section                         */
/*-------------------------------------------------------------------------*/

/*!
 * \addtogroup System
 */

/*@{*/


/*-------------------------------------------------------------------------*/
/*                         start of code                                   */
/*-------------------------------------------------------------------------*/


/*!
 * \brief ISR MainBeat Timer Interrupt (Timer 2 for Mega128, Timer 0 for Mega256).
 *
 * This routine is automatically called during system
 * initialization.
 *
 * resolution of this Timer ISR is 4,448 msecs
 *
 * \param *p not used (might be used to pass parms from the ISR)
 */
static void SysMainBeatInterrupt(void *p)
{

    /*
     *  scan for valid keys AND check if a MMCard is inserted or removed
     */
    KbScan();
    CardCheckCard();
}

/*!
 * \brief Initialise Digital IO
 *  init inputs to '0', outputs to '1' (DDRxn='0' or '1')
 *
 *  Pull-ups are enabled when the pin is set to input (DDRxn='0') and then a '1'
 *  is written to the pin (PORTxn='1')
 */
void SysInitIO(void)
{
    /*
     *  Port B:     VS1011, MMC CS/WP, SPI
     *  output:     all, except b3 (SPI Master In)
     *  input:      SPI Master In
     *  pull-up:    none
     */
    outp(0xF7, DDRB);

    /*
     *  Port C:     Address bus
     */

    /*
     *  Port D:     LCD_data, Keypad Col 2 & Col 3, SDA & SCL (TWI)
     *  output:     Keyboard colums 2 & 3
     *  input:      LCD_data, SDA, SCL (TWI)
     *  pull-up:    LCD_data, SDA & SCL
     */
    outp(0x0C, DDRD);
    outp((inp(PORTD) & 0x0C) | 0xF3, PORTD);

    /*
     *  Port E:     CS Flash, VS1011 (DREQ), RTL8019, LCD BL/Enable, IR, USB Rx/Tx
     *  output:     CS Flash, LCD BL/Enable, USB Tx
     *  input:      VS1011 (DREQ), RTL8019, IR
     *  pull-up:    USB Rx
     */
    outp(0x8E, DDRE);
    outp((inp(PORTE) & 0x8E) | 0x01, PORTE);

    /*
     *  Port F:     Keyboard_Rows, JTAG-connector, LED, LCD RS/RW, MCC-detect
     *  output:     LCD RS/RW, LED
     *  input:      Keyboard_Rows, MCC-detect
     *  pull-up:    Keyboard_Rows, MCC-detect
     *  note:       Key row 0 & 1 are shared with JTAG TCK/TMS. Cannot be used concurrent
     */
#ifndef USE_JTAG
    sbi(JTAG_REG, JTD); // disable JTAG interface to be able to use all key-rows
    sbi(JTAG_REG, JTD); // do it 2 times - according to requirements ATMEGA128 datasheet: see page 256
#endif //USE_JTAG

    outp(0x0E, DDRF);
    outp((inp(PORTF) & 0x0E) | 0xF1, PORTF);

    /*
     *  Port G:     Keyboard_cols, Bus_control
     *  output:     Keyboard_cols
     *  input:      Bus Control (internal control)
     *  pull-up:    none
     */
    outp(0x18, DDRG);
}

/*!
 * \brief Starts or stops the 4.44 msec mainbeat of the system
 * \param OnOff indicates if the mainbeat needs to start or to stop
 */
static void SysControlMainBeat(u_char OnOff)
{
    int nError = 0;

    if (OnOff==ON)
    {
        nError = NutRegisterIrqHandler(&OVERFLOW_SIGNAL, SysMainBeatInterrupt, NULL);
        if (nError == 0)
        {
            init_8_bit_timer();
        }
    }
    else
    {
        // disable overflow interrupt
        disable_8_bit_timer_ovfl_int();
    }
}


/*-------------------------------------------------------------------------*/
/* global variable definitions                                             */
/*-------------------------------------------------------------------------*/
int isAlarmSyncing;
/*-------------------------------------------------------------------------*/
/* local variable definitions                                              */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Thread init                                                             */
/*-------------------------------------------------------------------------*/
THREAD(StartupInit, arg)
{
    isAlarmSyncing = 1;
    NetworkInit();

    NtpSync();

    char* content = httpGet("/getAlarmen.php?radioid=DE370");
    parseAlarmJson(content);
    isAlarmSyncing = 0;

    free(content);
    NutThreadExit();
}

/*-------------------------------------------------------------------------*/
/* Global functions                                                        */
/*-------------------------------------------------------------------------*/

int timer(time_t start){
    time_t diff = time(0) - start;
    return diff;
}

int checkOffPressed(){
    if (KbScan() < -1){
        LcdBackLight(LCD_BACKLIGHT_ON);
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    unsigned char rightSave;
	time_t start;
    time_t startVolumeTime;
	int running = 0;

    WatchDogDisable();

    NutDelay(100);

    SysInitIO();

	SPIinit();

	LedInit();

	LcdLowLevelInit();

    Uart0DriverInit();
    Uart0DriverStart();
	LogInit();

    CardInit();

    X12Init();

    LcdBackLight(LCD_BACKLIGHT_ON);
    NtpInit();

    NutThreadCreate("BackgroundThread", StartupInit, NULL, 1024);

    /** Quick fix for turning off the display after 10 seconds boot */
    start = time(0);
    startVolumeTime = time(0);
    running = 1;

    RcInit();

	KbInit();

    SysControlMainBeat(ON);             // enable 4.4 msecs heartbeat interrupt

    /*
     * Increase our priority so we can feed the watchdog.
     */
    NutThreadSetPriority(1);

	/* Enable global interrupts */
	sei();
    unsigned char left = 64;
    unsigned char right = 64;
    displayDate(1);
    for (;;)
    {
        printf("%d \n", KbScan());
		//Check if a button is pressed
		if (checkOffPressed() == 1){
			start = time(0);
			running = 1;
            LcdBacklightKnipperen(startLCD);
		}

		//Check if background LED is on, and compare to timer
		if (running == 1){
			if (timer(start) >= 10){
				running = 0;
				LcdBackLight(LCD_BACKLIGHT_OFF);
			}
		}

        if(!isAlarmSyncing && X12RtcGetStatus(5) > 0)
        {
			displayAlarm(0,1);
			if (KbScan() < -1 || checkTime() == 1){
				handleAlarm();
				LcdBackLight(LCD_BACKLIGHT_OFF);
			}
        }
        else {
            displayTime(0);
                if (timer(startVolumeTime) >= 10) {
                    startVolumeTime = time(0);
                    printf("%d \n", left);
                    left = rightSave;
                    displayDate(1);
                   // printf("%d \n", right);
                }
            }


        if(KbScan() == -2049)
        {
            startVolumeTime = time(0);
            if(left > 1){
            left -= 8;
            right = left;
            VsSetVolume (left, right);
            //LogMsg_P(LOG_INFO, PSTR("klikU : %d"), right/8);
              // LogMsg_P(LOG_INFO, PSTR("klikU : %d"), left);
              //  printf("%d \n", right);
            displayVolume(left/8);
                }
            rightSave = left;
        }
        if(KbScan() == -1025)
        {
            startVolumeTime = time(0);
            if(left < 128) {
                left += 8;
                right = left;
                VsSetVolume(left, right);
               // LogMsg_P(LOG_INFO, PSTR("klikD : %d"), right/8);
               // LogMsg_P(LOG_INFO, PSTR("klikD : %d"), left);
                //printf("%d \n", right);
                displayVolume(left/8);
                rightSave = left;
            }
        }
        WatchDogRestart();
    }

    return(0);
}
