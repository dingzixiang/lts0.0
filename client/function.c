#include "function.h"
void menu1()
{   
    system("clear");
    printf("\t\t****聊天室****\t\t\n");
    printf("\t\t****1.登录****\t\t\n");
    printf("\t\t****2.注册****\t\t\n");
    printf("\t\t****3.退出****\t\t\n");
}
void menu3()
{
    system("clear");
    printf("\t\t****注册ID****\t\t\n");
    printf("\t\t****注册密码****\t\t\n");
    printf("\t\t****重复密码****\t\t\n");
    printf("\t\t****人机验证****\t\t\n");
    printf("\t\t****返回主菜单****\t\t\n");
}
void login()
{
    ;
}
int enroll()
{
    system("clear");;
    char a='0'; 
    char ID[32]={0};
    char pass[16]={0};
    int id=0,state=0;
    q[o].cmd=2;
    q[o].destination=0;
    printf("请输入");
    printf("\t\t****你注册的ID****\t\t\n");
    gets(ID);
    strncat(q[o].id,ID,32); 
    printf("请输入");
    printf("\t\t****你的密码****\t\t\n");
    gets(pass);
    strncat(q[o].buf,pass,16);
    if(send(sockfd,&q[o],sizeof(q[o]),0)==-1)
    {
        ERRLOG("send failed");
    }
    o++;
    return 0;
}
