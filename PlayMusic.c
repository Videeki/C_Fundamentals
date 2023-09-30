/*************************************************************************************************/
/*                                                                                               */
/*   Source: http://hzqtc.github.io/2012/05/play-mp3-with-libmpg123-and-libao.html               */
/*   Help: https://stackoverflow.com/questions/26007700/play-mp3-on-raspberry-with-mpg123-and-c  */
/*                                                                                               */
/*                                                                                               */
/*   Compiling -> Linux: gcc -O2 PlayMusic.c -o PlayMusic -lmpg123 -lao                          */
/*   Compiling -> Windows: gcc PlayMusic.c -o PlayMusic.exe -lwinmm                              */
/*                                                                                               */
/*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#include <windows.h>
    #include <mmsystem.h>

#elif __linux__
	#include <ao/ao.h>
    #include <mpg123.h>
    #define BITS 8

    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;
#else
    printf("Sorry, the system are not implemented yet... :'(\n")

#endif

int init();
int play(char *argv);
int close();



int main(int argc, char *argv[])
{
    puts("Version 0.4\n");

    if(argc<2)
    {
        puts("There is no music path");
        return -1;
    }

    puts("Music initialization");
    init();
    
    printf("Play the following music: %s\n", argv[1]);
    play(argv[1]);

    puts("Music closed");
    close();

    return 0;
}

int init()
{
    #ifdef _WIN32
        // Not neccesary the initialization //

    #elif __linux__
        // initializations //
        ao_initialize();
        driver = ao_default_driver_id();
        mpg123_init();
        mh = mpg123_new(NULL, &err);
        buffer_size = mpg123_outblock(mh);
        buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    #else
        printf("Sorry, the system are not implemented yet... :'(\n")

    #endif

    return 0;
}

int play(char *argv)
{
    #ifdef _WIN32
        char cmd[1024];
        sprintf(cmd, "open \"%s\" type mpegvideo alias mp3", argv);
        
        mciSendString(cmd, NULL, 0, NULL);
    
        mciSendString("play mp3 wait", NULL, 0, NULL);

    #elif __linux__
        // open the file and get the decoding format //
        mpg123_open(mh, argv);
        mpg123_getformat(mh, &rate, &channels, &encoding);

        // set the output format and open the output device //
        format.bits = mpg123_encsize(encoding) * BITS;
        format.rate = rate;
        format.channels = channels;
        format.byte_format = AO_FMT_NATIVE;
        format.matrix = 0;
        dev = ao_open_live(driver, &format, NULL);

        // decode and play //
        while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
            ao_play(dev, buffer, done);

    #else
        printf("Sorry, the system are not implemented yet... :'(\n")

    #endif

    return 0;
}

int close()
{
    #ifdef _WIN32
        // Not neccesary the initialization //

    #elif __linux__
        // clean up //
        free(buffer);
        ao_close(dev);
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        ao_shutdown();

    #else
        printf("Sorry, the system are not implemented yet... :'(\n")

    #endif

    return 0;
}
