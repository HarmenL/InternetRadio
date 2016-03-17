/*
 *  Copyright Jordy Sipkema, 2016.
 *
 *  Project             : 20152016-TI2.3a6-Internet Radio
 *  Module              : Eeprom
 *  File name           : Eeprom.h
 *  Revision            : 0.1
 *  Creation Date       : 2016/03/04
 *
 *  Description         : This module stores the non-volatile settings
 *                        for the radio in the atmega128's internal eeprom
 */

#ifndef MUTLI_OS_BUILD_EEPROM_H
#define MUTLI_OS_BUILD_EEPROM_H

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "typedefs.h"

#define EEPROM_BASE            0x0100 //The address where we'll start writing values.

#define SETTINGS_POINTER            ((TSettings *)EEPROM_USER_BASE)

/*!\brief System settings */
typedef struct _TSettingsSystem
{
    u_long  lSerialnumber;             // size = 4
} TSettingsSystem;                     // totalsize = 4

/*!\brief System Cache */
typedef struct _TCache
{
    tm last_sync;                      // TODO: figure out the size
} TCache;

typedef struct _TAlarmGeneral
{
    char snooze_time;                 // size = ?, desc: snooze_time in minutes.
} TAlarmGeneral;

typedef struct _TAlarm
{
    tm alarm_time;
    char name[16];
} TAlarm;

/*!\brief Settings to write on Eeprom */
typedef struct _TSettings
{
    size_t              Checksum;      // Checksum for validation TSettings-struct
    TSettingsSystem     System;        // System settings
    TAlarmGeneral       Alarm_general; // General alarms settings
    TCache              Cache;         // Cache
} TSettings;


extern void EepromRead(int, void*, size_t);
extern void EepromWrite(int, void*, size_t);

extern bool EepromGetAll(TSettings*);
extern void EepromSetAll(TSettings *settings);

extern bool EepromGetSystemSettings(TSettingsSystem*);

extern bool EepromGetCache(TCache*);
extern void EepromSetCache(TCache*);

#endif //MUTLI_OS_BUILD_EEPROM_H
