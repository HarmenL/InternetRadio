//
// Created by janco on 25-2-16.
//

#ifndef _Httpstream_H
#define _Httpstream_H

#include "ntp.h"

#define MAX_HEADERLINE 512
#define MSS 536
#define RX_TO 3000
#define TCPBUFSIZE 8760

extern bool HttpIsStreaming(void);
extern void playStream(char *ipaddr, u_short port, char *radiourl);
extern void stopStream(void);

#endif /* _Httpstream_H */
