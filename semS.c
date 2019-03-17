#include <sys/time.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxlen 4096
char buf[maxlen];


#define msgfile "/etc/shells"

// 消息结构
struct msg_form
{
    long mtype;
    char mtext[256];
};

int main()
{
    int msqid;
    key_t key;
    struct msg_form msg;

    // get IPC key
    if((key = ftok(msgfile,'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }
    printf("Message Queue - Server key is: %d.\n", key);


    if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
    {
        perror("msgget error");
        exit(1);
    }

    printf("My msqid is: %d.\n", msqid);
    printf("My pid is: %d.\n", getpid());

    for(;;) 
    {
        msgrcv(msqid, &msg, 256, 888, 0);// 返回类型为888的第一个消息
        printf("Server: receive msg.mtext is: %s.\n", msg.mtext);
        printf("Server: receive msg.mtype is: %d.\n", msg.mtype);

        msg.mtype = 777; // 客户端接收的消息类型
        sprintf(msg.mtext, "hello, I'm server %d", getpid());
        msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
    }
    return 0;
}
