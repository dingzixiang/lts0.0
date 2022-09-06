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
    int cmd;//1：登录 2：注册 3：查看全体在线成员 4：私发消息 5：群发消息 6:文件发送 7:文件接受 8:文件上传 9:文件下载 10:禁言 11：踢人 12:改权限
    char id[16];//登录id
    char destination[16];//0:服务器 all:全体   其他用户Id:个人
    char buf[N];//cmd 为1或2时为密码，3为空，4为消息内容
}QQ;
PP p;
QQ q;
QQ q1;
QQ qq[N];
static int o=0;
int sockfd;
void menu1();
void menuusr();
void menu3();


int login();
int logout();
int enroll();
int sifa();
int qunfa();
void look();
int wenjianout1();
int wenjianout2();
int wenjianin1();
int wenjianin2(FILE *fp); 
void *Myfun(void *m);
int jinyan();
int tiren();
int power();
int record();
#endif