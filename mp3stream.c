//
// Created by Jordy Sipkema on 28/03/16.
//

#include "mp3stream.h"

#include <sys/thread.h>



// Prototypes - Functions for internal use only! (They wont be visible outside this file!)
THREAD(Mp3Player, args);
void setVolume(void);

// Variables
static bool stream_stopped = false;
static bool stream_isplaying = false;
static u_char VS_volume = 7; //[0-15]; (Default volume = 7 (50%) )

bool play(FILE *stream)
{
    NutThreadCreate("Mp3Player", Mp3Player, stream, 512);
    printf("Mp3Player thread created. Device should start playing the stream.\n");

    return true;
}

u_char volumeUp(void)
{
    if (VS_volume >= 16)
        return VS_volume;

    //else:
    ++VS_volume;
    VS_volume = VS_volume % 17;

    setVolume();

    return VS_volume;
}

u_char volumeDown(void)
{
    if (VS_volume <= 0)
        return VS_volume;

    //else:
    --VS_volume;
    VS_volume = VS_volume % 17;
    setVolume();

    return VS_volume;
}

void setVolume(void){
    VsSetVolume((127 - (VS_volume * 8)) % 128);
}


THREAD(Mp3Player, args)
{
    FILE *stream = (FILE *)args;
    size_t rbytes = 0;
    char *mp3buf;
    int result = false;
    int nrBytesRead = 0;
    unsigned char iflag;

    //Whatevahhh
}

void killPlayerThread(void)
{
    stream_stopped = true;
}