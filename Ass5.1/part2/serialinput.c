#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // using the termios.h library
#include <sys/types.h>
#include <sys/stat.h>

#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;


int main(){
   int fd, count, c, res;
   struct termios options;       // the termios structure is vital
   unsigned char transmit[255];
   unsigned char receive[255];

   fd= open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

   if (fd<0){
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   tcgetattr(fd, &options);    // sets the parameters for the file

   // Set up the communications options:
   // 115200 baud, 8-bit, enable receiver, no modem control lines
//    options.c_cflag = B115200 | CRTSCTS | CS8 | CREAD | CLOCAL;

//    changing baud and fram setting to 57600 and 8-N-1
   // options.c_cflag &= ~(CSIZE | PARENB | CSTOPB);
   options.c_cflag = B57600 | CS8 | CREAD | CLOCAL;
   // options.c_iflag |= IGNPAR;
//    options.c_iflag = IGNPAR | ICRNL;   // ignore partity errors input modes
   options.c_oflag = IGNPAR | ICRNL;;   // output modes
   options.c_lflag = ICANON; //allowing input line editing


   tcflush(fd, TCIFLUSH);            // discard file information
   tcsetattr(fd, TCSANOW, &options); // changes occur immmediately

    while(STOP==FALSE){
        printf("Enter string: ");
        fgets(transmit, 255, stdin);
        usleep(100000);          
        
        count = write(fd, &transmit, sizeof(transmit)); // transmit
        if(count<0){
         perror("Failed to write to the output\n");
         return -1;
         }           
        usleep(100000);            

        count = read(fd, &receive, 255);
        if(count <0){
         perror("Failed to read from the input\n");
         return -1;
         }           
        if (count==0){
         printf("There was no data available to read!\n");}
        else{
         printf("The following was read in %s\n", transmit);}           


      //   printf("The following was read in %s\n", transmit);

        if (transmit[0] =='z'){
            STOP=TRUE;
            close(fd);}
    }
    close(fd);
    return 0;

}