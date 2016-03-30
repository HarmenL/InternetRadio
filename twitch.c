//
// Created by aares on 30-3-2016.
//

#include "twitch.h"

int streamid = 0;
struct streamdata data;

void setID(int id)
{
    streamid = id;
}

int getID()
{
    return streamid;
}