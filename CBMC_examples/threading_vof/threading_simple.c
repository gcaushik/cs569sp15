#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#define NUM_THREADS	4
 
// Let us create a global variable to change it in threads
int g = 0;
 
// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    printf("Global: %d\n", ++g);
}
 
int main()
{
    int i;
    pthread_t tid;
    pthread_t threads[NUM_THREADS];
 
    // Let us create threads
    for (i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, myThreadFun, (void *)i);
    
    for (i = 0; i < NUM_THREADS; i++)
    	pthread_join(threads[i],NULL);

    // printf("Global: %d\n", g);
    assert (g >= 0);
    assert (g <= NUM_THREADS);
    return 0; 
}