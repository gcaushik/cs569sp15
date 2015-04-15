#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#define NUM_THREADS	3
 
// Let us create a global variable to change it in threads
int g = 0;

pthread_mutex_t mutexsum;

// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    pthread_mutex_lock (&mutexsum);
    printf("Global: %d\n", ++g);
    pthread_mutex_unlock (&mutexsum);
}
 
int main()
{
    int i;
    pthread_t tid;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
 
    pthread_mutex_init(&mutexsum, NULL);
         
    /* Create threads to perform the dotproduct  */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Let us create threads
    for (i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], &attr, myThreadFun, (void *)i);
    
    pthread_attr_destroy(&attr);

    for (i = 0; i < NUM_THREADS; i++)
    	pthread_join(threads[i],NULL);

    // printf("Global: %d\n", g);
    assert (g == NUM_THREADS);
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);
    return 0; 
}