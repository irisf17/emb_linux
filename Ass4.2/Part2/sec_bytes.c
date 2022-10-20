#include <fcntl.h>
#include <unistd.h>
#include <string.h>


size_t count;
ssize_t ret;
// char *out_buffer[20];
char buf[400];



int main(){
        while(1){
            sleep(1);
            strcat(buf, "This is a test\n");
            count = strlen(buf);
            int fd = open("/dev/mydev", O_RDWR); //O_RDWR : flag to read+write
            ret = write(fd, buf, count);
            ret = close(fd);
        }
}

