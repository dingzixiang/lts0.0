#include "function.h"
int main(int argc, char **argv)
{
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==sockfd)
    {
        perror("socket");
        return -1;
    } 
    struct sockaddr_in serveraddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("192.168.12.13");
    serveraddr.sin_port=htons(atoi("8888"));
    socklen_t addrlen=sizeof(serveraddr);
    if(connect(sockfd,(struct sockaddr*)&serveraddr,addrlen)==-1)
    {
        perror("connect");
        return -1;
    }
    char x=0;
ONE:
    menu1();
    x=getchar();
    while ((ch = getchar()) != EOF && ch != '\n');
    switch (x)
    {
    case 49:
    login();
    break;
    case 50:
    enroll();
    goto ONE;
    break;
    case 51:
    exit(0);
    default:
    printf("错误输入,请重新输入\n");
    break;
    }
    return 0;
}