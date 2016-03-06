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
 *  COPYRIGHT (C) STREAMIT BV 2010
 *  \date 19 december 2003
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
/* global variable definitions                                             */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* local variable definitions                                              */
/*-------------------------------------------------------------------------*/


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


/* ����������������������������������������������������������������������� */
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
/* ����������������������������������������������������������������������� */
static void SysMainBeatInterrupt(void *p)
{

    /*
     *  scan for valid keys AND check if a MMCard is inserted or removed
     */
    KbScan();
    CardCheckCard();
}


/* ����������������������������������������������������������������������� */
/*!
 * \brief Initialise Digital IO
 *  init inputs to '0', outputs to '1' (DDRxn='0' or '1')
 *
 *  Pull-ups are enabled when the pin is set to input (DDRxn='0') and then a '1'
 *  is written to the pin (PORTxn='1')
 */
/* ����������������������������������������������������������������������� */
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
/* ����������������������������������������������������������������������� */
/*!
 * \brief Starts or stops the 4.44 msec mainbeat of the system
 * \param OnOff indicates if the mainbeat needs to start or to stop
 */
/* ����������������������������������������������������������������������� */
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

/*void handleAlarm(){
	struct _tm alarmtime;
    alarmtime = GetRTCTime();
    long flags;
	
    X12RtcGetAlarm(0,&alarmtime,0b11111111);
	alarmtime.tm_min = (alarmtime.tm_min-79);
	
	LogMsg_P(LOG_INFO, PSTR("Alarm : day = %02d,[%02d:%02d:%02d]"),alarmtime.tm_mday, alarmtime.tm_hour, alarmtime.tm_min, alarmtime.tm_sec);
	
	X12RtcSetAlarm(0,&alarmtime, 0b11111111);
	NutDelay(100);
}*/

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

/*void displayAlarm()
{
    struct _tm alarmtime;
    alarmtime = GetRTCTime();
    long flags;
    X12RtcGetAlarm(0,&alarmtime,0b11111111);
    NutDelay(100);
    char str[12];
    sprintf(str, "    %02d:%02d:%02d", alarmtime.tm_hour, alarmtime.tm_min - 80, alarmtime.tm_sec);
    LogMsg_P(LOG_INFO, PSTR("Alarm : [%02d:%02d:%02d]"), alarmtime.tm_hour, alarmtime.tm_min - 80, alarmtime.tm_sec );
    LcdArrayLineOne(str,12);

    char str2[6];
    sprintf(str2,"Wekker");
    LcdArrayLineTwo(str2,6);
    LcdBacklightKnipperen(startLCD);
}*/
/* ����������������������������������������������������������������������� */
/*!
 * \brief Main entry of the SIR firmware
 *
 * All the initialisations before entering the for(;;) loop are done BEFORE
 * the first key is ever pressed. So when entering the Setup (POWER + VOLMIN) some
 * initialisatons need to be done again when leaving the Setup because new values
 * might be current now
 *
 * \return \b never returns
 */
/* ����������������������������������������������������������������������� */

THREAD(StartupInit, arg)
{
    NetworkInit();
    NtpSync();
    char* content = httpGet("/getAlarmen.php?radioid=DE370");
    parseAlarmJson(content);
    free(content);
    NutThreadExit();
}

int main(void)
{
	time_t start;
	int running = 0;
	/* 
	 * Kroeske: time struct uit nut/os time.h (http://www.ethernut.de/api/time_8h-source.html)
	 *
	 */
	struct _tm alarmtime;
	/*
	 * Kroeske: Ook kan 'struct _tm gmt' Zie bovenstaande link
	 */
    /*
     *  First disable the watchdog
     */
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
    running = 1;

	/*
	 * Kroeske: sources in rtc.c en rtc.h
	 */

    if (At45dbInit()==AT45DB041B)
    {
        // ......
    }



    RcInit();
    
	KbInit();

    SysControlMainBeat(ON);             // enable 4.4 msecs hartbeat interrupt

    /*
     * Increase our priority so we can feed the watchdog.
     */
    NutThreadSetPriority(1);

	/* Enable global interrupts */
	sei();
	
    alarmtime = GetRTCTime();
    alarmtime.tm_sec = alarmtime.tm_sec+10;
    LogMsg_P(LOG_INFO, PSTR("alarmtime %02d-%02d-%04d || %02d-%02d-%02d"), alarmtime.tm_mday, alarmtime.tm_mon+1, alarmtime.tm_year+1900, alarmtime.tm_hour, alarmtime.tm_min, alarmtime.tm_sec);
	
    X12RtcSetAlarm(0,&alarmtime,0b11111111);
    NutDelay(100);
	
    for (;;)
    {		
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
        
		
        if(X12RtcGetStatus(5) > 0)
        {
			displayAlarm(0,1);
			if (KbScan() < -1 || checkTime() == 1){
				handleAlarm();
				LcdBackLight(LCD_BACKLIGHT_OFF);
			}
        }
        else {
            displayTime(0);
            displayDate(1);
        }
        WatchDogRestart();
    }

    return(0);      // never reached, but 'main()' returns a non-void, so.....
}
