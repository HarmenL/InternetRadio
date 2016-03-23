/*
 *  Copyright 20152016-TI2.3A6, 2016.
 *
 *  Project             : 20152016-TI2.3a6-Internet Radio
 *  Module              : NTP
 *  File name           : ntp.h
 *  Revision            : 1.1
 *  Creation Date       : 2016
 *
 *  Description         : This module syncs the time from a network time
 *                        server using the NTP-protocol.
 */

#ifndef _Ntp_H
#define _Ntp_H

#include "typedefs.h"

extern bool NtpIsSyncing(void);
extern void NtpInit(void);
extern void NtpSync(void);
extern bool NtpTimeIsValid(void);

void NtpCheckValidTime(void);
void NtpWriteTimeToEeprom(tm);
bool NtpCompareTime(tm, tm);
#endif /* _Ntp_H */
