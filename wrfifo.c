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

int main()
{
    char buf[maxlen];
    remove("tmpfifo");
    time_t tp;
    mkfifo("tmpfifo", 0666);
    int fd = open("tmpfifo", O_WRONLY);
    for(int i=0; i<10; ++i)
    {
        time(&tp);
        int n=sprintf(buf,"%c time is %s",'0'+i,ctime(&tp));
        printf("Send: %s", buf);
        write(fd, buf, n+1);
        //sleep(1);
    }
 
    //close(fd);
    return 0;
}
