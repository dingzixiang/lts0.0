#include "function.h"
int main(int argc, char **argv)
{
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==sockfd)
    {
        perror("socket");
        return -1;
    } 
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("192.168.12.13");
    serveraddr.sin_port=htons(atoi("9999"));
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(const char*)"192.168.12.13",sizeof(int));
    if(bind(sockfd, (struct sockaddr *)&serveraddr, addrlen) == -1) 
    { 
        ERRLOG("bind error"); 
    }
    if(listen(sockfd,5) == -1)
    {
        perror("listen");
        return -1;
    }
    fd_set readfds,tmpfds;
    FD_ZERO(&readfds);
    int maxfd=sockfd;
    int ret,i;
    FD_SET(sockfd,&readfds);
    int acceptfd[MAX]={0};
    while(1)
    {
        tmpfds=readfds;
        ret=select(maxfd+1,&tmpfds,NULL,NULL,NULL);
        if(-1==ret)
        {
            ERRLOG("select");
        }
        if(FD_ISSET(sockfd,&tmpfds))
        {
            for(i=0;i<MAX;i++)
            {
                if(acceptfd[i]==0)
                {
                    break;
                }
            }
            if((acceptfd[i]=accept(sockfd,(struct sockaddr*)&clientaddr,&addrlen))==-1)
            {
                ERRLOG("accept error"); 
            }
            printf("[%d]客户端%s:%d连接了 \n",acceptfd[i],inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
            FD_SET(acceptfd[i], &readfds);
            if(maxfd<acceptfd[i])
            {
                maxfd =acceptfd[i];
            }
        }
        else
        {
            for(i=0;i<MAX;i++)
            {
                if(FD_ISSET(acceptfd[i], &tmpfds))
                {
                    ret=recv(acceptfd[i],&q[o],sizeof(q[o]),0);
                    if (ret == -1)
                    {
                        ERRLOG("recv");
                    }
                    else if(ret == 0)
                    {
                        close(acceptfd[i]);
                        FD_CLR(acceptfd[i],&readfds);
                        printf("[%d]客户端%s:%d下线了 \n",acceptfd[i],inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
                    }
                    else
                    {
                        printf("[%d]客户端%s:%d收到了消息: %s\n",acceptfd[i],inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port),q[o].buf);
                        if(q[o].cmd==2)
                        {
                        enroll();
                        o++;
                        }
                    }
                    memset(buf,0,sizeof(buf));
                    break;
                }
            }
        }
    }
    return 0;
}