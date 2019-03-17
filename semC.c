#include <sys/time.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/msg.h>
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

    // 获取key值
    if ((key = ftok(msgfile, 'z')) < 0) 
    {
        perror("ftok error");
        exit(1);
    }

    // 打印key值
    printf("Message Queue - Client key is: %d.\n", key);

    // 打开消息队列
    if ((msqid = msgget(key, IPC_CREAT|0777)) == -1) 
    {
        perror("msgget error");
        exit(1);
    }

    // 打印消息队列ID及进程ID
    printf("My msqid is: %d.\n", msqid);
    printf("My pid is: %d.\n", getpid());

    // 添加消息，类型为888
    msg.mtype = 888;
    sprintf(msg.mtext, "hello, I'm client %d", getpid());
    msgsnd(msqid, &msg, sizeof(msg.mtext), 0);

    // 读取类型为777的消息
    msgrcv(msqid, &msg, 256, 777, 0);
    printf("Client: receive msg.mtext is: %s.\n", msg.mtext);
    printf("Client: receive msg.mtype is: %d.\n", msg.mtype);
    return 0;
}
