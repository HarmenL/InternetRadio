/*
 *  Copyright Jordy Sipkema, 2016.
 *
 *  Project             : 20152016-TI2.3a6-Internet Radio
 *  Module              : Eeprom
 *  File name           : Eeprom.h
 *  Revision            : 2.0
 *  Creation Date       : 2016/03/04
 *
 *  Description         : This module stores the non-volatile settings
 *                        for the radio in the atmega128's internal eeprom
 */

#include "eeprom.h"



void EepromRead(int addr, void* settings, size_t size){

}

void EepromWrite(int addr, void* settings, size_t size){

}

bool EepromGetAll(TSettings *settings){
    NutNvMemLoad(EEPROM_BASE, settings, sizeof(*settings));


    if (settings->Checksum != sizeof(*settings)){
        // Size mismatch: There is no valid configuration present.
        puts("EepromGetAll(): Size mismatch");
        return false;
    }

    return true;
}

void EepromSetAll(TSettings *settings){
    int success = NutNvMemSave(EEPROM_BASE, settings, sizeof(*settings));
    if (success == 0){ puts("EepromSetAll: SettingsSetAll successful."); }
    else { puts("EepromSetAll: SettingsSetAll successful."); }

    NutDelay(100);
}

void EepromWriteDefaults(void){
    puts("EepromWriteDefaults()");

    // Declare TSettings:
    TSettings settings;
    settings.Checksum = sizeof(settings);

    settings.Cache = (const struct TCache){ 0 };
    settings.System = (const struct TSettingsSystem){ 0 };

    EepromSetAll(&settings);
}


//bool EepromGetSystemSettings(TSettingsSystem *SystemSettings){
//
//}
//

bool EepromGetCache(TCache *cache){
    TSettings *settings;
    if (EepromGetAll(settings) == false){
        return false;
    }

    *cache = settings->Cache;
    return true;
}

void EepromSetCache(TCache *cache){
    TSettings settings;
    settings.Checksum = sizeof(settings);

    settings.System = (const struct TSettingsSystem){ 0 };
    settings.Cache = *cache;

    EepromSetAll(&settings);
}