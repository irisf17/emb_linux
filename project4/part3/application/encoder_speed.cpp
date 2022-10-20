// /**
//  * @file   testebbchar.c
//  * @author Derek Molloy
//  * @date   7 April 2015
//  * @version 0.1
//  * @brief  A Linux user space program that communicates with the ebbchar.c LKM. It passes a
//  * string to the LKM and reads the response from the LKM. For this example to work the device
//  * must be called /dev/ebbchar.
//  * @see http://www.derekmolloy.ie/ for a full description and follow-up descriptions.
// */

#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
 
//#define BUFFER_LENGTH 4             ///< The buffer length (crude but fine)

int main(){
    int ret, fd;

    //Enable gpio23
    fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "23", 2);
    close(fd);

    //Set gpio23 as output
    fd = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
    write(fd, "out", 3);
    close(fd);

    //Set gpio23 as high
    fd = open("/sys/class/gpio/gpio23/value", O_WRONLY);
    write(fd, "01", 2);
    close(fd);

    //Enable gpio24
    fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "24", 2);
    close(fd);

    //Set gpio24 as output
    fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
    write(fd, "out", 3);
    close(fd);

    // set gpio24 low
    fd = open("/sys/class/gpio/gpio24/value", O_WRONLY);
    write(fd, "00", 2);
    close(fd);

    // next we make gpio12 a PWM output
    fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);
    write(fd, "00", 2);
    close(fd);

    // set the period of pwm
    fd = open("/sys/class/pwm/pwmchip0/pwm0/period", O_WRONLY);
    write(fd, "100000", 6);
    close(fd);

    // set the duty cycle to 0ms
    fd = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
    write(fd, "20000", 5);
    close(fd);

    // enable the PWM
    fd = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
    write(fd, "01", 2);
    close(fd);

    sleep(60);
    // ret = close(fd);

    // set gpio23 low
    fd = open("/sys/class/gpio/gpio23/value", O_WRONLY);
    write(fd, "00", 2);
    close(fd);
    // set pwm low
    fd = open("/sys/class/gpio/gpio24/value", O_WRONLY);
    write(fd, "00", 2);
    close(fd);


    // disable gpio23, and pwm0
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd, "23", 2);
    close(fd);
    fd = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
    write(fd, "00", 2);
    close(fd);
    // fd = open("/sys/class/pwm/pwmchip0/unexport", O_WRONLY);
    // write(fd, "00", 2);
    // close(fd);

    printf("End of the program\n");
    return 0;
}