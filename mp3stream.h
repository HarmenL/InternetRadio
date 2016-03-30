//
// Created by Jordy Sipkema on 28/03/16.
//

#ifndef MUTLI_OS_BUILD_MP3STREAM_H
#define MUTLI_OS_BUILD_MP3STREAM_H

#include "typedefs.h"

#include <netinet/tcp.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>

bool play(void);
bool connectToStream(char* ipaddr, u_short port, char *radioUrl);
void killPlayerThread(void);

u_char volumeUp(void);
u_char volumeDown(void);
void setVolume(void); // Do not use this one, this is invoked by volumeUp/Down


#endif //MUTLI_OS_BUILD_MP3STREAM_H
