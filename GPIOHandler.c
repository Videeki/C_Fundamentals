// Compiling: gcc GPIOHandler.c -o Builds/GPIOHandler
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
    FILE *export;
    export = fopen("/sys/class/gpio/export", "w");

    if (export == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(export, "%d", pinNr);
    fclose(export);

    sleep(1);

    return 0;
}

int setupPIN(int pinNr, char *mode)
{
    
    char setupPin[50];
    FILE *direction;
    sprintf(setupPin, "/sys/class/gpio/gpio%d/direction", pinNr);
    direction = fopen(setupPin, "w");

    if (direction == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(direction, "%s", mode);
    fclose(direction);
       
    return 0;
}

int writePIN(int pinNr, int value)
{
    char pinPath[50];
    FILE *writePin;
    sprintf(pinPath, "/sys/class/gpio/gpio%d/value", pinNr);
    writePin = fopen(pinPath, "w");

    if (writePin == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(writePin, "%d", value);
    fclose(writePin);
    
    return 0;
}

int readPIN(int pinNr)
{
    int value;
    char pinPath[33];
    FILE *readPin;
    sprintf(pinPath, "/sys/class/gpio/gpio%d/value", pinNr);
    readPin = fopen(pinPath, "w");

    if (readPin == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(readPin, "%d", value);
    fclose(readPin);
   
    return value;
}

int deinitPIN(int pinNr)
{
    char deinitPin[35];
    FILE *unexport;
    unexport = fopen("/sys/class/gpio/unexport", "w");

    if (unexport == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(unexport, "%d", pinNr);
    fclose(unexport);

    return 0;
}