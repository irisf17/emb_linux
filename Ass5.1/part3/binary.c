#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // using the termios.h library
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>



int main(){
  int fd, count;
  struct termios options;
  int number = 0;
  fd= open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd<0){
    perror("UART: Failed to open the file.\n");
  return -1;
  }
  tcgetattr(fd, &options);
  // // options.c_lflag = ICANON; //allowing input line editing
  // options.c_lflag &= ~ICANON; //disallowing input line editing
  cfmakeraw(&options);

  options.c_cflag &= ~(CSIZE | PARENB | CSTOPB);
  options.c_cflag = B115200 | CS8 | CREAD | CLOCAL; // control modes
  options.c_iflag = IGNPAR | ICRNL;   // input mode, ignore partity errors
  options.c_oflag = IGNPAR | ICRNL;  // output modes
  /* set input mode (non-canonical, no echo,...) */
  // options.c_lflag &= ~ICANON; // local modes
  // options.c_lflag |= ICANON; // local modes

  options.c_cc[VTIME]=0; /* no timer */
  options.c_cc[VMIN]=4; /* minimum number
of characters */


  tcflush(fd, TCIFLUSH);            // discard file information
  
  // setting linux port to raw mode
  tcsetattr(fd, TCSANOW, &options); // changes occur immmediately
 
  while(1){
      printf("The number is %d \n", number);
      // scanf("%22d", &number);
      usleep(100000);
      // write all (four) bytes of the counter
      count = write(fd, &number, sizeof(number)); // transmit
      if(count<0){
        perror("Failed to write to the output\n");
        return -1;
      }

      usleep(100000);

      int res_num;
      count = read(fd, &res_num, 22);
      if(count <0){
        perror("Failed to read from the input\n");
        return -1;
      }

      if (count==0){
        printf("There was no data available to read!\n");}
      else{
        printf("The following number was read: %d with size of %d \n", number, count);
      }
      number++;
  }

}
