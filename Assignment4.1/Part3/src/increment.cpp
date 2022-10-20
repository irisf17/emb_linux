#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "../include/increment.h"
#include <pthread.h>
#include "fifo.h"

extern pthread_mutex_t sharedVariableMutex;
extern int32_t gSharedVariable;
extern Fifo f;
void *incrementTask(void *param)
{
    while (1)
    {
        /* Delay for 3 seconds. */
        sleep(3);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        if(!f.circular_is_full()){
                f.circular_put(gSharedVariable++);
                printf("Increment buffer: %d\n", gSharedVariable);
                printf("Number of items in buffer: %d\n", f.position);}
        else{
                printf("FIFO BUFFER is full \n");}
        //printf("Increment Task: shared var is %d\n", gSharedVariable);
        /* Release the mutex for other task to use. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}