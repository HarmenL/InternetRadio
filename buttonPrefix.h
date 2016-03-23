//
// Created by malek on 23-3-2016.
//

#ifndef INTERNETRADIO_BUTTONPREFIX_H
#define INTERNETRADIO_BUTTONPREFIX_H

#endif //INTERNETRADIO_BUTTONPREFIX_H

struct _LeftButtons getButtonPrefix();

struct _LeftButtons
{
    u_short id;
    u_short bid;
    char name[16];
    char ip[24];
    u_short port;
    char url[24];
};
