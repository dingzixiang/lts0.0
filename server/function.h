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
#include <pthread.h>
#define N 128
#define MAX 1024
#define ERRLOG(errmsg) do{\
                        perror(errmsg);\
                        printf("%s - %s - %d\n", __FILE__, __func__, __LINE__);\
                        exit(1);\
                        }while(0)
int ch;
int sockfd;
pthread_mutex_t mutex;
typedef struct sta
{
    char id[16];        //登录id
    char pass[16];      //用户密码
    int state;          //0:未登录   1:登录
    int power;          //0:普通用户 1:超级用户
    int say;            //0:正常聊天   1:被禁言
    int acceptfd;       //fd
    int count;          //计数 
}PP;
typedef struct msg
{
    int cmd;                //1：登录 2：注册 3：查看全体在线成员 4：私发消息 5：群发消息 6.文件发送方 7.文件接受方
    char id[16];            //登录来源id
    char destination[16];   //0:服务器 all:全体   其他用户Id:个人
    char buf[N];            //cmd 为1或2时为密码，3为空，45或为消息内容，6为文件名或同意/拒绝传送
}QQ;
PP p[MAX];
QQ q[MAX];


int login(int fd);
int logout(int fd);
int enroll(int fd);
int enroll1();
int look(int fd);
int sifa(int fd);
int qunfa(int fd);
int wenjianin(int fd);
int wenjianout(int fd);
int upload(int fd,FILE *fp);
int download(int fd);
int jinyan(int fd);
#endif