#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // using the termios.h library
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <pthread.h>

uint32_t counter = 0;
uint32_t res_counter = 0;
int fd, count;

pthread_t writeTaskObj;
pthread_t readTaskObj;

void *counter_write(void *param);
void *counter_read(void *param);

void *counter_write(void *param){
    while(1){
        sleep(1);
        printf("The number is %d \n", counter);
        // scanf("%22d", &number);
        // write all (four) bytes of the counter
        count = write(fd, &counter, sizeof(counter)); // transmit
        if(count<0){
            perror("Failed to write to the output\n");}
        counter++;
    }
}


void *counter_read(void *param){
    while(1){
        count = read(fd, &res_counter, sizeof(counter));
        if(count <0){
            perror("Failed to read from the input\n");}
        if (count==0){
            printf("There was no data available to read!\n");}
        else{
            printf("The following number was read: %d with size of %d \n", res_counter, count);
      }
  }
}
    

int main(){
  fd= open("/dev/ttyS0", O_RDWR | O_NOCTTY);
  if (fd<0){
    perror("UART: Failed to open the file.\n");
  return -1;}
  struct termios options;
  tcgetattr(fd, &options);
  // // options.c_lflag = ICANON; //allowing input line editing
  // options.c_lflag &= ~ICANON; //disallowing input line editing
  cfmakeraw(&options);

//   options.c_cflag &= ~(CSIZE | PARENB | CSTOPB);
  options.c_cflag = B115200 | CS8 | CREAD | CLOCAL; // control modes
  options.c_iflag = IGNPAR | ICRNL;   // input mode, ignore partity errors
//   options.c_oflag = IGNPAR | ICRNL;  // output modes
  /* set input mode (non-canonical, no echo,...) */
  // options.c_lflag &= ~ICANON; // local modes
  // options.c_lflag |= ICANON; // local modes

//   options.c_cc[VTIME]=0; /* no timer */
  options.c_cc[VMIN]=4; /* minimum number of characters */ //4 bytes


  tcflush(fd, TCIFLUSH);            // discard file information
  // setting linux port to raw mode
  tcsetattr(fd, TCSANOW, &options); // changes occur immmediately
  /* Create the increment and decrement tasks using the default task
    * attributes. Do not pass in any parameters to the tasks. */
    pthread_create(&writeTaskObj, NULL, counter_write, NULL);
    pthread_create(&readTaskObj, NULL, counter_read, NULL);

    /* Allow the tasks to run. */
    pthread_join(writeTaskObj, NULL);
    pthread_join(readTaskObj, NULL);
    close(fd);

    return 0;      

}
