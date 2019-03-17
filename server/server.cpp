#include "config.h"

using namespace std;
const int maxevents=5;
static char buf[Maxline];

//数据接受 buf
#define recvlen 4095
char recvBuf[recvlen];
struct epoll_event eventList[maxevents];

void RecvData(int fd);
void AcceptConn(int srvfd,int epollfd);

int main()
{
    int listenfd;
    sodrin_t servaddr;



    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(Sport);

    if (bind(listenfd, (sodr_t *) &servaddr, sizeof(servaddr)) != 0)
    {
        printf("bind error: %s", strerror(errno));
        return 0;
    }

    if (listen(listenfd, Sport) != 0)
    {
        printf("listen error");
        return 0;
    }
    
    /*
    int connfd = accept(listenfd, nullptr, nullptr);
    printf(" server\n");
    */

    /////////////////////////////////////////////////////////////////////////////////////////////////

    // epoll 初始化
    auto epollfd = epoll_create(maxevents);
    struct epoll_event event;
    event.events = EPOLLIN|EPOLLET;
    event.data.fd = listenfd;
    
    //add Event
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event) < 0)
    {
        printf("epoll add fail : fd = %d\n", listenfd);
        return -1;
    }
    
    //epoll
    while(1)
    {
        auto timeout=3000;      
        //epoll_wait
        int ret = epoll_wait(epollfd, eventList, maxevents, timeout);
        
        if(ret < 0)
        {
            printf("epoll error\n");
            break;
        }
        else if(ret == 0)
        {
            printf("timeout ...\n");
            continue;
        }
        
        //直接获取了事件数量,给出了活动的流,这里是和poll区别的关键
        int i = 0;
        for(i=0; i<ret; i++)
        {
            //错误退出
            if ((eventList[i].events & EPOLLERR) ||
                (eventList[i].events & EPOLLHUP) ||
                !(eventList[i].events & EPOLLIN))
            {
              printf ( "epoll error\n");
              close (eventList[i].data.fd);
              return -1;
            }
            
            if (eventList[i].data.fd == listenfd)
            {
                printf("new user,%d, in\n",eventList[i].data.fd);
                AcceptConn(listenfd,epollfd);
            }
            else
            {
                printf("data from user,%d",eventList[i].data.fd);
                RecvData(eventList[i].data.fd);
            }
        }
    }
    
    close(epollfd);
    close(listenfd);

    ////////////////////////////////////////////////////////////////////////////////////////

    /*
        for(;;)
        {
            int n;
            while((n = recv(connfd, buf, Maxline, 0))>0)
            {
                buf[n] = '\0';
                std::cout<<buf<<std::endl;
            }
        }
        close(connfd);
    */

}

/**************************************************
函数名：AcceptConn
功能：接受客户端的链接
参数：srvfd：监听SOCKET
***************************************************/
void AcceptConn(int srvfd,int epollfd)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(struct sockaddr_in);
    bzero(&sin, len);
 
    int confd = accept(srvfd, (struct sockaddr*)&sin, &len);
 
    if (confd < 0)
    {
       printf("bad accept\n");
       return;
    }else
    {
        printf("Accept Connection: %d", confd);
    }
    //将新建立的连接添加到EPOLL的监听中
    struct epoll_event event;
    event.data.fd = confd;
    event.events =  EPOLLIN|EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, confd, &event);
}    



//读取数据
void RecvData(int fd)
{
    int ret;
    int recvLen = 0;
    
    memset(recvBuf, 0, recvlen);
    printf("RecvData function\n");
    
    if(recvLen != recvlen)
    {
        while(1)
        {
            //recv数据
            ret = recv(fd, (char *)recvBuf+recvLen, recvlen-recvLen, MSG_DONTWAIT);
            if(ret == 0)
            {
                recvLen = 0;
                break;
            }
            else if(ret < 0)
            {
                recvLen = 0;
                break;
            }
            //数据接受正常
            recvLen = recvLen+ret;
            if(recvLen<recvlen)
            {
                continue;
            }
            else
            {
                //数据接受完毕
                printf("buf = %s\n",  recvBuf);
                recvLen = 0;
                break;
            }
        }
    }
 
    printf("data is %s", recvBuf);
}

