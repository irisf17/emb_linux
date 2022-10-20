#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // using the termios.h library
#include<stdint.h>
#include <pthread.h>

// pthread_mutex_t = sharedVariableMutex;


uint8_t counter = 245;
uint8_t received_counter = 0;
int fd, count;

pthread_t write_incrementObj;
pthread_t read_printObj;
// device opened for blocking read
void *write_i(void *param);
void *read_p(void *param);


void *write_i(void *param)
{
   while(1)
   {
      sleep(1);
    //   pthread_mutex_lock(&sharedVariableMutex);
      if ((count = write(fd, &counter, sizeof(counter)))<0) // transmit
         {         
            perror("Failed to write to the output\n");
            // return -1;
         }
      counter++;
    //   pthread_mutex_unlock(&sharedVariableMutex);
   }
}

void *read_p(void *param)
{
   while(1)
   {
    //   pthread_mutex_lock(&sharedVariableMutex);
      if ((count = read(fd, &received_counter, sizeof(counter)))<0) // receive
            {         
               perror("Failed to read from the input\n");
            //    return -1;
            }
      if (count==0) 
         {
            printf("There was no data available to read!\n");
         }
      else 
         {
            printf("\n%d\n", received_counter);
            printf("characters in the serial buffer is: %d\n", count);
         }
    //   pthread_mutex_unlock(&sharedVariableMutex);
}
}



int main(){
    fd= open("/dev/ttyS0", O_RDWR | O_NOCTTY);

    struct termios options;       // the termios structure is vital
    tcgetattr(fd, &options);    // sets the parameters for the file

   cfmakeraw(&options); // set raw mode

   options.c_cc[VMIN] = 4;
   //options.c_cc[VTIME] = 0;
   //options.c_cflag = B57600;
   
   tcflush(fd, TCIFLUSH);            // discard file information
   
   tcsetattr(fd, TCSANOW, &options); // changes occur immmediately
   
   //const size_t MSG_LEN = 1;
   //uint32_t msg[MSG_LEN];  
   
   /* Create the mutex for accessing the shared variable using the
   * default attributes. */
//    pthread_mutex_init(&sharedVariableMutex, NULL);
   /* Create the increment and decrement tasks using the default task
   * attributes. Do not pass in any parameters to the tasks. */
   pthread_create(&write_incrementObj, NULL, write_i, NULL);
   pthread_create(&read_printObj, NULL, read_p, NULL);
   /* Allow the tasks to run. */
   pthread_join(write_incrementObj, NULL);
   pthread_join(read_printObj, NULL);
   
   
   close(fd);
   return 0;
}