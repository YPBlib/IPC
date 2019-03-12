#include "config.h"

//using namespace std;

static char buf[Maxline];

namespace cat
{
    enum state{nologin,online};
}



int main(int argc,char* argv[])
{
    int sockfd, numbytes;
    char buf[BUFSIZ];
    struct sockaddr_in servaddr;
    while ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(Sport);

    if (inet_pton(AF_INET,argv[1] , &servaddr.sin_addr) < 0)
    {
        printf("inet_pton error, exit");
        exit(1);
    }

     if (connect(sockfd, (sodr_t *) &servaddr, sizeof(servaddr)) < 0)
     {
        printf("connect to server error, exit\n");
        fprintf(stderr, "error in CreateProcess: %s", strerror(errno));
        exit(1);
    }
    else
    {
        printf("connect success\n");
    }

    for(;;)
	{
		/*try
		{
			auto z = Parse();
			if (z == nullptr)
				break;
			else toysql::exec<decltype(z)>(z);
		}
		catch (std::runtime_error& s)
		{
			std::cout << s.what() << std::endl;
			skip_exp();
		}*/
        char msg[4096]={0};
        std::cin>>msg;
        send(sockfd,msg,strlen(msg),0);
        std::cout<<"send return"<<std::endl;
	}

    return 0;
}


