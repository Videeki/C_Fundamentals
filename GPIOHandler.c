// Compiling: gcc GPIOHandler.c -o GPIOHandler -l wiringPi

#include <wiringPi.h>

void blink (const int led)
{
    digitalWrite(led, HIGH);
    delay(30);
    digitalWrite(led, LOW);
    delay(30);
}

int main(void)
{
    int led = 23;
    wiringPiSetupGpio();
    
    pinMode(led,OUTPUT);
    delay(10); 
    
    while(1)
    {
	    blink(led);
	}
    
    return 0;
}