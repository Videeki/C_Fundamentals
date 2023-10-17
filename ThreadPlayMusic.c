// Compiling gcc -O2 -o ThreadPlayMusic ThreadPlayMusic.c -lmpg123 -lao -lpthread

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

#include "PlayMusic.h"
#include "Queue.h"


string_Queue_t playlist;
int run = 1;
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void* musicPlayer();


   
int main()
{
    pthread_t thread_id;
    int i = 0;
    char path[255];
    obtain(&playlist, "MusicQueue", 100);

    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, musicPlayer, NULL);
    int cmd;
    while(run)
    {
        puts("\n");
        printf("1.Add music\n");
        printf("2.List playlist\n");
        printf("3.Nr of music\n");
        printf("4.Exit\n");
        printf("Enter your choice of operations : ");
        scanf("%d", &cmd);
        
        switch (cmd)
        {
            case 1:
            {
                char temp[255];
                scanf("%s", temp);
                enqueue(&playlist, temp);
                break;
            }
            
            case 2:
            {
                show(&playlist);
                break;
            }

            case 3:
            {
                printf("Nr of Elements: %d\n", nrOfElements(&playlist));
                break;
            }

            case 4:
            {
                run = 0;
                break;
            }

            case 5:
            {
                exit(0);
            }
            
            default:
            printf("Incorrect choice \n");
        }
    }
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    flush(&playlist);
    
    return 0;
}


void* musicPlayer()
{
    char path[255];

    //puts("Music initialization");
    initMusic();
    
    while(run)
    {
        if(nrOfElements(&playlist) == 0)
        {
            sleep(1);
        }
        else
        {   
            playMusic(dequeue(&playlist));
        }
        
    }
    
    //puts("Music closed");
    closeMusic();

}
