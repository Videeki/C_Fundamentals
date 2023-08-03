#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
  
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
    int i = 0;
    for(i = 0; i < 50; i++)
    {
        printf("Printed thread %d times\n", i);
        sleep(1);
    }
    
    return NULL;
}
   
int main()
{
    pthread_t thread_id;
    int i = 0;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    for(i = 0; i < 100; i++)
    {
        printf("Printed main %d times\n", i);
        sleep(1);
    }
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}