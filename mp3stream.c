//
// Created by Jordy Sipkema on 28/03/16.
//

#include "mp3stream.h"

#include <arpa/inet.h>
#include <sys/bankmem.h>
#include <sys/heap.h>
#include <sys/thread.h>
#include <sys/timer.h>

#include "vs10xx.h"

#define OK              1
#define NOK             0
#define DEFAULT_VOLUME  7
#define MSIZE           1024
#define NUTSEGBUFFER    4096

typedef struct _StreamArgs {
    FILE *stream;
} TStreamArgs;

// Prototypes - Functions for internal use only! (They wont be visible outside this file!)
THREAD(Mp3Player, args);
int ProcessStreamMetaData(FILE *stream);

// Variables
static bool stream_connected = false;
static bool stream_stopped = false;

static u_char VS_volume = DEFAULT_VOLUME; //[0-16]; (Default volume = 7/16
static u_long metaInt = 0;

FILE *stream;
TCPSOCKET *socket;

bool connectToStream(u_long ipAddressStream, u_short port, char *radioUrl
)
{
    stream_connected = false;
    bool result = true;
    char* data;

    socket = NutTcpCreateSocket();
    if (NutTcpConnect(socket, inet_addr("62.195.226.247"), port))
    {
        // An error has occurred.
        printf("ConnectToStream: Error creating tcp socket.\n");
        NutSleep(5000);
        result = false;
        return result;
    }

    stream = _fdopen((int)socket, "r+b");

    // Tell the console what we are doing.
    printf("GET %s HTTP/1.0\r\n", radioUrl);

    fprintf(stream, "GET %s HTTP/1.0\r\n", radioUrl);
    fprintf(stream, "Host: %s\r\n", inet_ntoa(ipAddressStream));
    fprintf(stream, "User-Agent: Ethernut\r\n");
    fprintf(stream, "Accept: */*\r\n");
    fprintf(stream, "Icy-MetaData: 1\r\n");
    fprintf(stream, "Connection: close\r\n\r\n");
    fflush(stream);

    // Server will respond with a HTTP-header. Fetch it to the buffer.
    stream_connected = true;
    stream_stopped = false;

    data = (char *)malloc(MSIZE * sizeof(char));

    while (fgets(data, MSIZE, stream))
    {
        /*
         * Chop off the carriage return at the end of the line. If none
         * was found, then this line was probably too large for our buffer.
         */
        char *cp = strchr(data, '\r');
        if (cp == 0) continue;             // Input buffer overflow.

        *cp = 0;

        /*
         * The header is terminated by an empty line.
         */
        if (*data == 0) break;

        if (strncmp(data, "icy-metaint:", 12) == 0)
            metaInt = atol(data + 12);
        printf("%s\n", data);
    }

    free(data);

    return result;
}

bool play()
{
    if (stream_connected == false)
        return false;

    // else:

    TStreamArgs *streamArgs = &(TStreamArgs){
            .stream = stream,
            //.metaint = metaInt
    };

    NutThreadCreate("Mp3Player", Mp3Player, streamArgs, 512);
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
    u_char volumeToSet = (128 - (VS_volume * 8)) % 129;
    VsSetVolume(volumeToSet, volumeToSet);
    printf("- VS_volume level: %d/16\n", VS_volume);
}

void killPlayerThread(void)
{
    printf("Signal to stop the stream sent.\n");
    stream_stopped = true;
}

THREAD(Mp3Player, args)
//void function(void* args) //TODO: REMOVE THIS, THIS IS ONLY TO TRICK CLION!
{
    // Unpack the args passed to the thread initializer.
    TStreamArgs *streamArgs = (TStreamArgs *)args;
    FILE *stream = streamArgs->stream;

    int result = NOK;

    size_t rbytes = 0;
    char *mp3buf;
    u_char ief;
    int got = 0;
    u_long mp3left = metaInt;

    // Init MP3-buffer. NutSegBuf is a global system buffer.
    if (0 != NutSegBufInit(NUTSEGBUFFER)){
        // Reset the global buffer.
        ief = VsPlayerInterrupts(0);
        NutSegBufReset();
        VsPlayerInterrupts(ief);

        result = OK;
    }

    // Init the VS1003b hardware.
    if (result == OK){
        if (-1 == VsPlayerInit()) {
            if (-1 == VsPlayerReset(0)){
                result = NOK;
            }
        }
    }

    for(;;)
    {
        /*
         * Query the number of bytes available in the MP3 buffer.
         */
        ief = VsPlayerInterrupts(0);
        mp3buf = NutSegBufWriteRequest(&rbytes);
        VsPlayerInterrupts(ief);

        /*
         * If the player is not running, kick it.
         * This should only occur once.
         */
        if (VsGetStatus() != VS_STATUS_RUNNING) {
            puts("Player not running.");
            if (rbytes < 1024){
                puts("Kick player in 3 2 1..:");
                VsPlayerKick();
            }
        }

        setVolume();

        /*
         * Do not read pass metadata.
         * This causes ugly hiccups.
         */
        if (metaInt && rbytes > mp3left){
            rbytes = mp3left;
        }

        /*
         * Read directly into the MP3 buffer.
         */
        while (rbytes) {
            if (stream_stopped == true) {
                printf("Signal to stop the stream recieved\n.");
                stream_connected = false;
                VsPlayerStop();
                NutTcpCloseSocket(socket);
                NutThreadExit();
            }

            if ((got = fread(mp3buf, 1, rbytes, stream)) > 0) {
                ief = VsPlayerInterrupts(0);
                mp3buf = NutSegBufWriteCommit(got);
                VsPlayerInterrupts(ief);

                if (metaInt) {
                    mp3left -= got;
                    if (mp3left == 0) {
                        ProcessStreamMetaData(stream);
                        mp3left = metaInt;
                    }
                }

                if (got < rbytes && got < 512) {
                    printf("%lu buffered\n", NutSegBufUsed());
                    NutSleep(250);
                }
                else {
                    NutThreadYield();
                }
            } else {
                break;
            }
            rbytes -= got;
        }

        if (got <= 0) break;


    } // end for(;;)

}

int ProcessStreamMetaData(FILE *stream)
{
    u_char blks = 0;
    u_short cnt;
    int got;
    int rc = 0;
    u_char *mbuf;

    /*
     * Wait for the lenght byte.
     */
    got = fread(&blks, 1, 1, stream);
    if(got != 1) {
        return -1;
    }
    if (blks) {
        if (blks > 32) {
            printf("Error: Metadata too large, %u blocks\n", blks);
            return -1;
        }

        cnt = blks * 16;
        if ((mbuf = malloc(cnt + 1)) == 0) {
            printf("Can't malloc memory for metadata parsing\n");
            return -1;
        }

        /*
         * Receive the metadata block.
         */
        for (;;) {
            if ((got = fread(mbuf + rc, 1, cnt, stream)) <= 0) {
                return -1;
            }
            if ((cnt -= got) == 0) {
                break;
            }
            rc += got;
            mbuf[rc] = 0;
        }

        printf("\nMeta='%s'\n", mbuf);
        free(mbuf);
    }
    return 0;
}
