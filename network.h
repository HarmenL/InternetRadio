//
// Created by janco on 25-2-16.
//

#ifndef _Network_H
#define _Network_H

#include "typedefs.h"

extern void NetworkInit(void);
extern void httpGet(char address[], void (*parser)(char*));
char* getMacAdress();


#endif /* _Network_H */
