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
   int file, count_write, count_read;
   const size_t MSG_LEN = 6;
   uint8_t msg[MSG_LEN];
   uint8_t bla1;
   uint8_t bla2;
   uint8_t ble1;
   uint8_t ble2;

   if(argc!=5){ //number of inputs +1
       printf("Invalid number of arguments, expected 4 but got: %d exiting!\n", argc-1);
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
   options.c_cc[VMIN] = 6; //length of text message

   tcflush(file, TCIFLUSH);
   tcsetattr(file, TCSANOW, &options);
   
   uint16_t tala1 = atoi(argv[3]);
   uint16_t tala2 = atoi(argv[4]);

   bla1 = (tala1 >> 8) & 0xff; //converting to hex
   bla2 = (tala1 >> 0) & 0xff; //converting to hex

   ble1 = (tala2 >> 8) & 0xff; //converting to hex
   ble2 = (tala2 >> 0) & 0xff; //converting to hex

    msg[0] = atoi(argv[1]);
    msg[1] = atoi(argv[2]);
    msg[2] = bla1;
    msg[3] = bla2;
    msg[4] = ble1;
    msg[5] = ble2;


   // writing the 6 bytes to the uart port, also they are changed to binary with rawmode
   count_write = write(file, msg, MSG_LEN);
   if (count_write<0){
      perror("Failed to write to the output\n");
      return -1;
   }
   if(count_write>0){
        printf("Sent request: ");
        int i=0;
        while (i < sizeof(msg))
        {
            printf("%02X ",msg[i]);
            i++;
        }
    printf("\n");
   }

   usleep(100000);

   unsigned char receive[100];
   
   count_read = read(file, (void*)receive, 100);
   if (count_read<0){
      perror("Failed to read from the input\n");
      return -1;
   }

   if (count_read==0) printf("There was no data available to read!\n");
   else {
      receive[count_read]=0;  //There is no null character sent by the Arduino
      printf("Received reply: ");
      int i = 0;
      while (i < sizeof(msg))
        {
            printf("%02X ",receive[i]);
            i++;
        }
    printf("\n");
   }

   close(file);
   return 0;
}
