//
// Created by janco on 25-2-16.
//

#ifndef _Network_H
#define _Network_H


extern void NetworkInit(void);
char* httpGet(char address[]);
void parseAlarmJson(char* content);

#endif /* _Network_H */
