//
// Created by janco on 25-2-16.
//

#ifndef _Ntp_H
#define _Ntp_H

typedef enum {false, true} bool;

extern bool NtpIsSyncing(void);
extern void NtpInit(void);
extern void NtpSync(void);
extern bool NtpTimeIsValid(void);

void NtpCheckValidTime(void);
void NtpWriteTimeToEeprom(tm);
bool NtpCompareTime(tm, tm);
#endif /* _Ntp_H */
