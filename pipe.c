#include <sys/time.h>
#include <sys/select.h>
#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define maxlen 4096

int main()
{
    int p2c[2]; // parent to child
    int c2p[2]; // child to parent
    pid_t pid;
    char buff[maxlen];

    if(pipe(p2c)<0 || pipe(c2p)<0)  // create pipe
    {
        fprintf(stderr,"Create Pipe Error!\n");
        exit(1);
    }

    if((pid = fork()) < 0)
    {
        fprintf(stderr,"Fork Error!\n");
        exit(1);
    }
    else if(pid > 0)  // parent. write to p2c[1]. read from c2p[0].
    {
        struct timeval* pto;
        struct timeval timeout;
        fd_set readfds,writefds;

        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(c2p[0],&readfds);

        close(p2c[0]);
        close(c2p[1]);
        write(p2c[1], "P", 1);

        
        int ready=select(c2p[0]+1,&readfds,NULL,NULL,pto);
        read(c2p[0],buff,maxlen);
        printf("%s\n", buff);


    }
    else    // child
    {
        close(c2p[0]);
        close(p2c[1]);
        read(p2c[0], buff, maxlen);
        printf("%s\n", buff);
        write(c2p[1], "C", 1);
    }

    return 0;
}
