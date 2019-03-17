#include <sys/time.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "semun.h"

#define maxlen 4096
char buf[maxlen];




int main(int argc,char** argv)
{
    struct semid_ds ds;
    struct sembuf sop;
    union semun arg,dummy;
    int semid,j;

    semid=5;
    arg.buf=&ds;
    semctl(semid,0,IPC_STAT,arg);
   
    return 0;
}