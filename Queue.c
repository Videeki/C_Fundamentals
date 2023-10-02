#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_BUFFER 8
int bufferLength = 0;
int readIndex = 0;
int writeIndex = 0;
int circularBuffer[SIZE_OF_BUFFER];

int enqueue();
int dequeue();
int nrOfElements();
int show();

int main(int argc, char* argv[])
{
    int ch;
    while (1)
    {


        printf("1.Enqueue Operation\n");
        printf("2.Dequeue Operation\n");
        printf("3.Display the Queue\n");
        printf("4.Exit\n");
        printf("Enter your choice of operations : ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
            enqueue();
            break;
            case 2:
            dequeue();
            break;
            case 3:
            show();
            break;
            case 4:
            exit(0);
            default:
            printf("Incorrect choice \n");
        } 
    } 
    return 0;
}

int enqueue()
{
    if(bufferLength == SIZE_OF_BUFFER)
    {
        printf("Buffer is full!\n");
        return -1;
    }
    
    scanf("%d", &circularBuffer[writeIndex]);

    bufferLength++;
    writeIndex++;

    if(writeIndex == SIZE_OF_BUFFER)
    {
        writeIndex = 0;
    }

    return 0;
}

int dequeue()
{
    if(bufferLength == 0) 
    {
        printf("Buffer is empty!\n");
        return -1;
    }

    printf("The output value is %d\n", circularBuffer[readIndex]);

    bufferLength--;
    readIndex++;

    if(readIndex == SIZE_OF_BUFFER) 
    {
        readIndex = 0;
    }
    
    return 0;
}

int nrOfElements()
{
    return 0;
}

int show()
{
    int i = 0;
    if(bufferLength == 0) 
    {
        printf("Buffer is empty!\n");
        return -1;
    }

    for(i = readIndex; i < bufferLength; i++)
    {
        printf("%d ", circularBuffer[i]);
    }
    printf("\n");
    return 0;
}