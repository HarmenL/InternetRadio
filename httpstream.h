//
// Created by janco on 25-2-16.
//

#ifndef _Httpstream_H
#define _Httpstream_H

#include "ntp.h"

extern bool HttpIsStreaming();
extern void playStream(char *ipaddr, u_short port, char *radiourl);
extern void stopStream();


#endif /* _Httpstream_H */