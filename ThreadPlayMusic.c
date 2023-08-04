// Compiling gcc -O2 -o ThreadPlayMusic ThreadPlayMusic.c -lmpg123 -lao -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <ao/ao.h>
#include <mpg123.h>
#include <wiringPi.h>

#define BITS 8
  
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void* playMusic(void *path);
const buttons[4] = {2,14,17,23};
//enum 
void* gpiohandling(void *targs);
   
int main()
{
    pthread_t thread_id;
    int i = 0;

    char path[] = "/media/videeki/Adatok/Zene/Vegyes/Amánjó főiskola he.mp3";

    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, playMusic, (void*)&path);
    for(i = 0; i < 100; i++)
    {
        printf("Printed main %d times\n", i);
        sleep(1);
    }
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}

void* playMusic(void *path)
{
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

    /* initializations */
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    /* open the file and get the decoding format */
    mpg123_open(mh, (char*)path);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    /* set the output format and open the output device */
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    /* decode and play */
    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        ao_play(dev, buffer, done);

    /* clean up */
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();

    return 0;
}

void* gpiohandling(void *state)
{
    switch ((int)state)
    {
        case 0:
        {
            wiringPiSetupGpio();
            for(int i = 0; i < sizeof(buttons); i++)
            {
                pinMode(buttons[i],INPUT);
                delay(10);
            }
            break;  
        }
        case 1:
        {
            for(int i = 0; i < sizeof(buttons); i++)
            {
                digitalRead(buttons[i]);
                delay(10);
            } 
            break;  
        }
        default:
        {
            run = FALSE;
            break;
        }
    }
}