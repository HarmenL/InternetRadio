//
// Created by aares on 30-3-2016.
//

#ifndef INTERNETRADIO_TWITCH_H
#define INTERNETRADIO_TWITCH_H

#endif //INTERNETRADIO_TWITCH_H

void setID(int id);
int getID(void);
int streamid;
struct streamdata data;

struct streamdata
{
    char title[20];
    char name[20];
    char game[20];
};
