#include "function.h"
void login()
{
    ;
}
int enroll()
{
//    system("clear");
    sqlite3 *ppdb;
    char a='0'; 
    char id[16]={0};
    char pass[16]={0};
    int state=0;
    char sql[256]={0};
    int ret = sqlite3_open("stu.db",&ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    sprintf(sql,"create table if not exists stu(id char,password char,state int,power int,say int);");
    ret =sqlite3_exec(ppdb,sql,NULL,NULL,NULL);
    if(ret != SQLITE_OK)
    {
    printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
    return -1;
    }
    memset(sql,0,sizeof(sql));    
    sprintf(sql,"insert into stu values('%s','%s',0,0,0);",q[o].id,q[o].buf);
    ret=sqlite3_exec(ppdb,sql,NULL,NULL,NULL);
    if(ret != SQLITE_OK)
    {
        printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
        return -1;
    }
    memset(sql,0,sizeof(sql));
    sprintf(sql,"select * from stu;");
    char **result;
    int row,column;
    ret=sqlite3_get_table(ppdb,sql,&result,&row,&column,NULL);
    if(ret!=SQLITE_OK)
    {
        printf("sqlite3_get_table:%s\n",sqlite3_errmsg(ppdb));
        return -1;
    }
    int i=0,j=0;
    int index=column;
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
            printf(" %s=%s ",result[j],result[index]);
            index++;
        }
        putchar(10);
    }
    return 0;
}
