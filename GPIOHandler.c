// Compiling: gcc GPIOHandler.c -o GPIOHandler -l wiringPi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define ON 1
#define OFF 0

int initPIN(int pinNr);
int setupPIN(int pinNr, char *mode);
int writePIN(int pinNr, int value);
int readPIN(int pinNr);
int deinitPIN(int pinNr);

int main(int argc, char* argv[])
{
    //int LED = atoi(argv[1]);
    int LED = 23;
    char mode[] = "out";

    initPIN(LED);
    puts("Init DONE!");
    setupPIN(LED, mode);
    puts("Setup DONE!");
    puts("Let's get ready to RUMBLE!!!");

    for(int i = 0; i < 10; i++)
    {
        writePIN(LED, ON);
        puts("ON");
        sleep(1);
        writePIN(LED, OFF);
        puts("OFF");
        sleep(1);
    }
    puts("GAME OVER");
    deinitPIN(LED);
    puts("Deinit DONE!");
    puts("Good Bye Sucker!");
}

int initPIN(int pinNr)
{
    char initPin[33];
    sprintf(initPin, "echo %d > /sys/class/gpio/export", pinNr);
    system(initPin);
    sleep(1);

    return 0;
}

int setupPIN(int pinNr, char *mode)
{
    char setupPin[50];
    sprintf(setupPin, "echo %s > /sys/class/gpio/gpio%d/direction", mode, pinNr);
    system(setupPin);
    sleep(1);
    
    return 0;
}

int writePIN(int pinNr, int value)
{
    char writePin[50];
    sprintf(writePin, "echo %d > /sys/class/gpio/gpio%d/value", value, pinNr);
    system(writePin);
    sleep(0.1);
    
    return 0;
}

int readPIN(int pinNr)
{
    int value;
    char readPin[33];
    sprintf(readPin, "cat /sys/class/gpio/gpio%d/value", pinNr);
    // Do the magic tricks
    sleep(0.1);
    
    return value;
}

int deinitPIN(int pinNr)
{
    char deinitPin[35];
    sprintf(deinitPin, "echo %d > /sys/class/gpio/unexport", pinNr);
    system(deinitPin);
    sleep(0.1);
    
    return 0;
}