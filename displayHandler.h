//
// Created by Jordy Sipkema on 26/02/16.
//

#ifndef MUTLI_OS_BUILD_DISPLAYHANDLER_H
#define MUTLI_OS_BUILD_DISPLAYHANDLER_H
#include "ntp.h"

void displayTime(int);
void displayDate(int);
void displayAlarm(int line_number, int line_numberTwo, int idx);
void displayVolume(int pos);
void displayTwitch(char name[], char title[], char game[]);
bool isDisplayingCustomMessage();
void setDisplayingCustomMessage(bool value);

#endif //MUTLI_OS_BUILD_DISPLAYHANDLER_H
