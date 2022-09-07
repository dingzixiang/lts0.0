#include "function.h"
int main(int argc, char **argv)
{
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==sockfd)
    {
        perror("socket");
        return -1;
    } 
    struct sockaddr_in serveraddr,clientaddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("192.168.12.13");
    serveraddr.sin_port=htons(atoi("8888"));
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(const char*)"192.168.12.13",sizeof(int));
    socklen_t addrlen=sizeof(serveraddr);
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
    char buf[N]={0};
    enroll1();
    sqlite3 *ppdb1;
    char sql1[256]={0};
    memset(sql1,0,sizeof(sql1));
    int ret1 = sqlite3_open("record.db",&ppdb1); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb1)); 
    return -1;
    }
    sprintf(sql1,"create table if not exists record(id char,destination char,buf char);");
    ret1 =sqlite3_exec(ppdb1,sql1,NULL,NULL,NULL);
    if(ret1 != SQLITE_OK)
    {
    printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb1));
    return -1;
    }
    ret1 = sqlite3_close(ppdb1); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb1)); 
    return -1;
    }
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
                    ret=recv(acceptfd[i],&q[acceptfd[i]],sizeof(q[acceptfd[i]]),0);
                    if (ret == -1)
                    {
                        ERRLOG("recv");
                    }
                    else if(ret == 0)
                    {
                        logout(acceptfd[i]);
                        close(acceptfd[i]);
                        FD_CLR(acceptfd[i],&readfds);
                        printf("[%d]客户端%s:%d下线了 \n",acceptfd[i],inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
                    }
                    else
                    {
                        printf("[%d]客户端%s:%d收到了消息: %s\n",acceptfd[i],inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port),q[acceptfd[i]].buf);
                        if(q[acceptfd[i]].cmd==2)
                        {
                            enroll(acceptfd[i]);
                        }
                        if(q[acceptfd[i]].cmd==1)
                        {
                            login(acceptfd[i]);
                        }
                        if(q[acceptfd[i]].cmd==3)
                        {
                        //    pthread_mutex_init(&mutex,NULL); //动态初始化一把锁
                            look(acceptfd[i]);
                        }
                        if(q[acceptfd[i]].cmd==4)
                        {
                            sifa(acceptfd[i]);
                        }
                        if(q[acceptfd[i]].cmd==5)
                        {
                            qunfa(acceptfd[i]);
                        }
                        if(q[acceptfd[i]].cmd==6)
                        {
                            wenjianin(acceptfd[i]);
                        }
                        if(q[acceptfd[i]].cmd==7)
                        {
                            wenjianout(acceptfd[i]);
                        }
                        if(q[acceptfd[i]].cmd==8)
                        {
                            FILE *fp = fopen(q[acceptfd[i]].destination,"a"); 
                            if(NULL == fp) 
                            { 
                                perror("fopen"); 
                                return -1; 
                            }
                            upload(acceptfd[i],fp);
                            fclose(fp);
                        }
                        if(q[acceptfd[i]].cmd==9)
                        {
                            download(acceptfd[i]);
                        }
                        if(q[acceptfd[i]].cmd==10)
                        {
                            jinyan(acceptfd[i]);
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