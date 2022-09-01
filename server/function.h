#ifndef _FUNCTION_
#define _FUNCTION_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <sys/select.h>
#include <sys/time.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <sys/stat.h>
#include <errno.h>
#define N 128
#define MAX 1024
#define ERRLOG(errmsg) do{\
                        perror(errmsg);\
                        printf("%s - %s - %d\n", __FILE__, __func__, __LINE__);\
                        exit(1);\
                        }while(0)
int ch;
int sockfd;
typedef struct sta
{
    char id[16];        //登录id
    char pass[16]; //用户密码
    int state; //0:未登录   1:登录
    int power; //0:普通用户 1:超级用户
    int say;   //0:被禁言   1:正常聊天
}PP;
typedef struct msg
{
    int cmd;//1：登录 2：注册 3：查看全体在线成员 4：发消息
    char id[16];//登录id
    int destination;//0:服务器1:全体2:个人
    char buf[N];//cmd 为1或2时为密码，3为空，4为消息内容
}QQ;
PP p[MAX];
QQ q[MAX];
static int o=0;


void login();
int enroll();
#endif