#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // using the termios.h library

int main(){
   int fd, count;

   fd= open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
   if (fd<0){
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   struct termios options;       // the termios structure is vital
   tcgetattr(fd, &options);    // sets the parameters for the file

   // Set up the communications options:
   // 115200 baud, 8-bit, enable receiver, no modem control lines
   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;   // ignore partity errors input modes
   options.c_oflag = IGNPAR | ICRNL;   // output modes
   options.c_lflag = ICANON; //allowing input line editing


   tcflush(fd, TCIFLUSH);            // discard file information
   tcsetattr(fd, TCSANOW, &options); // changes occur immmediately

   unsigned char transmit[20] = "Hello Raspberry Pi!\n";  // send string

    if ((count = write(fd, &transmit, 22))<0){         // transmit
      perror("Failed to write to the output\n");
      return -1;
   }

   usleep(100000);             // give the remote machine a chance to respond

   unsigned char receive[22]; //declare a buffer for receiving data

   if ((count = read(fd, (void*)receive, 22))<0){   //receive data
      perror("Failed to read from the input\n");
      return -1;
   }

   if (count==0){
      printf("There was no data available to read!\n");}
   else{
      printf("The following was read in [%d]: %s\n",count,transmit);
   }

   close(fd);
   return 0;
}