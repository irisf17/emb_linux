#include <stdio.h>
#include <unistd.h>
#include "../include/decrement.h"
#include <pthread.h>
#include <stdint.h>
#include <fifo.h>

extern pthread_mutex_t sharedVariableMutex;
extern int32_t gSharedVariable;
extern Fifo f;
void *decrementTask(void *param)
{
    while (1)
    {
        /* Delay for 7 seconds. */
        sleep(7);
        /* Wait for the mutex to become available. */
        pthread_mutex_lock(&sharedVariableMutex);
        if(!f.circular_is_full()){
                f.circular_get();
                gSharedVariable--;
                printf("Decrement buffer: %d\n", gSharedVariable);
        }
        else{
                printf("FIFO BUFFER is full \n");}
        /* Release the mutex. */
        pthread_mutex_unlock(&sharedVariableMutex);
    }
}