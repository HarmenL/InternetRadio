//
// Created by Jordy Sipkema on 28/03/16.
//

#ifndef MUTLI_OS_BUILD_MP3STREAM_H
#define MUTLI_OS_BUILD_MP3STREAM_H

#include <stdio.h>
#include <string.h>

#include "typedefs.h"

bool play(FILE *stream);

u_char volumeUp(void);
u_char volumeDown(void);


#endif //MUTLI_OS_BUILD_MP3STREAM_H
