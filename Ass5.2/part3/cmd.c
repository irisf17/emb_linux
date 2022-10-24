/* Simple send and receive C example (line-mode terminal program with local echo) 
* for communicating with the Arduino using /dev/ttyS0. */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>
#include<stdint.h>
#include <stdlib.h> //library for atoi()


int main(int argc, char *argv[]){
   int file, count;
   const size_t MSG_LEN = 2;
   uint8_t msg[MSG_LEN];

   if(argc!=3){
       printf("Invalid number of arguments, expected 2 but got: %d exiting!\n", argc);
       return -2;
   }

   if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   struct termios options;

   tcgetattr(file, &options);

   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;

   cfmakeraw(&options); // set raw mode
   options.c_cc[VMIN] = 2;

   tcflush(file, TCIFLUSH);
   tcsetattr(file, TCSANOW, &options);

    msg[0] = atoi(argv[1]);
    msg[1] = atoi(argv[2]);

   // writing the 2 bytes to the uart port, also they are changed to binary with rawmode
   if (count = write(file, msg, 2)<0){
      perror("Failed to write to the output\n");
      return -1;
   }

   usleep(100000);

   unsigned char receive[100];

   if ((count = read(file, (void*)receive, 100))<0){
      perror("Failed to read from the input\n");
      return -1;
   }

   if (count==0) printf("There was no data available to read!\n");
   else {
      receive[count]=0;  //There is no null character sent by the Arduino
      printf("The following was read in [%d]: %s\n",count,receive);
   }

   close(file);
   return 0;
}
