//
// Created by janco on 25-2-16.
//

#ifndef _Httpstream_H
#define _Httpstream_H

#include "typedefs.h"

extern bool HttpIsStreaming(void);
extern void playStream(char *ipaddr, u_short port, char *radiourl);
extern void stopStream(void);


#endif /* _Httpstream_H */
