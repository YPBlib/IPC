#include <sys/time.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/stat.h>
#include<fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxlen 4096
char buf[maxlen];

int main()
{
   
    int fd = open("tmpfifo", O_RDONLY);           
    while(read(fd, buf, maxlen)>0)
    printf("%s", buf);
      
    


    close(fd);  // 关闭FIFO文件
    return 0;
}
