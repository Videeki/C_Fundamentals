#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_BUFFER 8
int bufferLength = 0;
int readIndex = 0;
int writeIndex = 0;
char circularBuffer[SIZE_OF_BUFFER][255];

//int obtain(int *maxQueueSize);  //Returns a reference to a queue.
int enqueue();  //Adds an element to the back of a queue.
int dequeue();  //Removes an element from the front of a queue and returns the element.
//int preview();  //Returns the element at the front of the queue without removing the element from the queue.
//int getStatus();    //Returns information about the current state of a queue, such as the number of elements currently in the queue.
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

//int obtaion(int *maxQueueSize)
//{
//
//    return 0;
//}

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
    if(bufferLength == 0) 
    {
        printf("Buffer is empty!\n");
        return -1;
    }

    int i = readIndex;
    while(i != writeIndex)
    {
        printf("%s ", circularBuffer[i]);
        i++;
        if(i == SIZE_OF_BUFFER)
        {
            i = 0;
        }
    }
    
    printf("\n");
    return 0;
}