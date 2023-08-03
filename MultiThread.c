// Compiling: gcc MultiThread.c -o /home/videeki/C_Fundamentals/Builds/MultiThread -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// Let us create a global variable to change it in threads
int g = 0;

// The function to be executed by all threads
void *myThreadFun(char *vargp)
{
	// Store the value argument passed to this thread
	char *myid = vargp;
	//printf("%s", vargp);
	// Let us create a static variable to observe its changes
	static int s = 0;

	// Change static and global variables
	++s; ++g;

	// Print the argument, static and global variables
	printf("Thread ID: %s, Static: %d, Global: %d\n", myid, ++s, ++g);
}

int main()
{
	int i;
	pthread_t tid;
	char str[] = "Hello";
	printf("%s\n", str);

	// Let us create three threads
	for (i = 0; i < 3; i++)
		pthread_create(&tid, NULL, myThreadFun, &str);

	pthread_exit(NULL);
	return 0;
}
