#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint16_t checksumCalculator(uint8_t * data, uint16_t length)
{
   uint16_t curr_crc = 0x0000;
   uint8_t sum1 = (uint8_t) curr_crc;
   uint8_t sum2 = (uint8_t) (curr_crc >> 8);
   int index;
   for(index = 0; index < length; index = index+1)
   {
      sum1 = (sum1 + data[index]) % 255;
      sum2 = (sum2 + sum1) % 255;
   }
   return (sum2 << 8) | sum1;
}
int main() {
   // put your setup code here, to run once:
   printf("\n");
   uint8_t buffer[10] = {1,2,3,4,5,6,7,8,9,0};
   uint16_t crc = checksumCalculator(buffer,10);
   printf("Calculated CRC is: %02X : ", crc);
   printf("\n");
}

