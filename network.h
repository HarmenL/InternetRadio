//
// Created by janco on 25-2-16.
//

#ifndef _Network_H
#define _Network_H

#include "typedefs.h"

bool hasNetworkConnection(void);
bool NetworkIsReceiving(void);
extern void NetworkInit(void);
char* httpGet(char address[]);
char* getMacAdress();
void parseAlarmJson(char* content);
int getTimeZone(void);

#endif /* _Network_H */
