#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_BUFFER 8
int bufferLength = 0;
int readIndex = 0;
int writeIndex = 0;
char circularBuffer[SIZE_OF_BUFFER][255];

int enqueue();
int dequeue();
int nrOfElements();
int show();

int main(int argc, char* argv[])
{
    int ch;
    while (1)
    {
        int i = 0;
        for(i = 0; i < SIZE_OF_BUFFER; i++)
        {
            printf("%s ", circularBuffer[i]);
        }
        printf("\n\n");

        printf("1.Enqueue Operation\n");
        printf("2.Dequeue Operation\n");
        printf("3.Display the Queue\n");
        printf("4.Display number of elements\n");
        printf("5.Exit\n");
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
            nrOfElements();
            break;
            case 5:
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
    
    scanf("%s", circularBuffer[writeIndex]);

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

    printf("The output value is %s\n", circularBuffer[readIndex]);
    //circularBuffer[readIndex] = "";

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
    printf("Nr of elements: %d\n", bufferLength);
    return bufferLength;
}

int show()
{
    int i = 0;
    if(bufferLength == 0) 
    {
        printf("Buffer is empty!\n");
        return -1;
    }

    if(readIndex < writeIndex)
    {
        for(i = readIndex; i <= writeIndex; i++)
        {
            printf("%s ", circularBuffer[i]);
        }
    }
    else if(readIndex > writeIndex)
    {
        for(i = writeIndex; i <= readIndex; i++)
        {
            printf("%s ", circularBuffer[i]);
        }
    }
    else
    {
        printf("Buffer is empty!\n");
    }
    
    printf("\n");
    return 0;
}