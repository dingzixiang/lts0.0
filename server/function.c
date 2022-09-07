#include "function.h"
int login(int fd)
{
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
    sprintf(sql,"select * from stu where id = '%s';",q[fd].id);
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
        printf("用户存在\n");
        for(j=0;j<column;j++)
        {
            printf(" %s=%s ",result[j],result[index]);
            printf(" index=%d\n",index);
            index++;
        }
        putchar(10);
    }
    if(strcmp(result[8],"1")==0)
    {
        printf("已登录\n");
        strcpy(q[fd].buf,"已登录\n");
        ret=send(fd,&q[fd],sizeof(q[fd]),0);
        if (ret == -1)
        {
            ERRLOG("send");
        }
    }
    if(strcmp(result[7],q[fd].buf)==0&&strcmp(result[8],"0")==0)
    {
        printf("密码正确，未登录\n");
        memset(sql,0,sizeof(sql)); 
        sprintf(sql,"update stu set state =1 where id = '%s';",q[fd].id);
        ret =sqlite3_exec(ppdb,sql,NULL,NULL,NULL);
        if(ret != SQLITE_OK)
        {
        printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
        return -1;
        }
        memset(sql,0,sizeof(sql)); 
        sprintf(sql,"update stu set acceptfd =%d where id = '%s';",fd,q[fd].id);
        ret =sqlite3_exec(ppdb,sql,NULL,NULL,NULL);
        if(ret != SQLITE_OK)
        {
        printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
        return -1;
        }
        printf("登录成功\n");
        strcpy(q[fd].buf,"登录成功\n");
        ret=send(fd,&q[fd],sizeof(q[fd]),0);
        if (ret == -1)
        {
            ERRLOG("send");
        }
    }    
    ret = sqlite3_close(ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }    
    return 0;
}
int logout(int fd)
{
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
    sprintf(sql,"update stu set state =0 where acceptfd = %d;",fd);
    ret =sqlite3_exec(ppdb,sql,NULL,NULL,NULL);
    if(ret != SQLITE_OK)
    {
    printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
    return -1;
    }
}
int enroll1()
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
    sprintf(sql,"create table if not exists stu(id char,password char,state int,power int,say int,acceptfd int);");
    ret =sqlite3_exec(ppdb,sql,NULL,NULL,NULL);
    if(ret != SQLITE_OK)
    {
    printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
    return -1;
    }
    memset(sql,0,sizeof(sql));
    sprintf(sql,"select * from stu;");
    char **result1;
    int row1,column1;
    ret=sqlite3_get_table(ppdb,sql,&result1,&row1,&column1,NULL);
    if(ret!=SQLITE_OK)
    {
        printf("sqlite3_get_table:%s\n",sqlite3_errmsg(ppdb));
        return -1;
    }
    int i=0,j=0;
    for(i=0;i<row1;i++)
    {
        if(strcmp(result1[6+6*i],"root")==0)
        {
            ret = sqlite3_close(ppdb); 
            if(ret != SQLITE_OK) 
            { 
                printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
                return -1;
            }
            return 0;               
        }
    }
    memset(sql,0,sizeof(sql));    
    sprintf(sql,"insert into stu values('root','root',0,1,0,0);");
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
    ret = sqlite3_close(ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    return 0;
}
int enroll(int fd)
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
    sprintf(sql,"create table if not exists stu(id char,password char,state int,power int,say int,acceptfd int);");
    ret =sqlite3_exec(ppdb,sql,NULL,NULL,NULL);
    if(ret != SQLITE_OK)
    {
    printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
    return -1;
    }
    memset(sql,0,sizeof(sql));
    sprintf(sql,"select * from stu;");
    char **result1;
    int row1,column1;
    ret=sqlite3_get_table(ppdb,sql,&result1,&row1,&column1,NULL);
    if(ret!=SQLITE_OK)
    {
        printf("sqlite3_get_table:%s\n",sqlite3_errmsg(ppdb));
        return -1;
    }
    int i=0,j=0;
    for(i=0;i<row1;i++)
    {
        if(strcmp(result1[6+6*i],q[fd].id)==0)
        {
            printf("已注册\n");
            strcpy(q[fd].buf,"已注册\n");
            ret=send(fd,&q[fd],sizeof(q[fd]),0);
            if (ret == -1)
            {
                ERRLOG("send");
            }
            ret = sqlite3_close(ppdb); 
            if(ret != SQLITE_OK) 
            { 
                printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
                return -1;
            }
            return 0;               
        }
    }
    memset(sql,0,sizeof(sql));    
    sprintf(sql,"insert into stu values('%s','%s',0,0,0,%d);",q[fd].id,q[fd].buf,fd);
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
    strcpy(q[fd].buf,"未注册\n");
    ret=send(fd,&q[fd],sizeof(q[fd]),0);
    if (ret == -1)
    {
        ERRLOG("send");
    }
    ret = sqlite3_close(ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    return 0;
}
int look(int fd)
{
    sqlite3 *ppdb;
    char sql[256]={0};
    int ret = sqlite3_open("stu.db",&ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    sprintf(sql,"select * from stu where state = 1;");
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
    memset(q[fd].buf,0,sizeof(q[fd].buf));
    for(i=0;i<row;i++)
    {
        strcat(q[fd].buf,result[index]);
        strcat(q[fd].buf,"在线");
        for(j=0;j<column;j++)
        {
            printf(" %s=%s ",result[j],result[index]);
            index++;
        }
        putchar(10);
    }
    strcat(q[fd].buf,"\0");
    ret=send(fd,&q[fd],sizeof(q[fd]),0);
    if (ret == -1)
    {
        ERRLOG("send");
    }
    ret = sqlite3_close(ppdb); 
    if(ret != SQLITE_OK) 
    { 
        printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
        return -1;
    }
    return 0;
}
int sifa(int fd)
{
    sqlite3 *ppdb;
    sqlite3 *ppdb1;
    int fd1;
    char sql[256]={0};
    char sql1[256]={0};
    int ret1 = sqlite3_open("record.db",&ppdb1); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb1)); 
    return -1;
    }
    memset(sql1,0,sizeof(sql1)); 
    sprintf(sql1,"insert into record values('%s','%s','%s');",q[fd].id,q[fd].destination,q[fd].buf);
    ret1=sqlite3_exec(ppdb1,sql1,NULL,NULL,NULL);
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
    int ret = sqlite3_open("stu.db",&ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    sprintf(sql,"select * from stu where id = %s;",q[fd].id);
    char **result;
    int row,column;
    ret=sqlite3_get_table(ppdb,sql,&result,&row,&column,NULL);
    if(ret!=SQLITE_OK)
    {
        printf("sqlite3_get_table:%s\n",sqlite3_errmsg(ppdb));
        return -1;
    }
    if(atoi(result[10])==1)
    {
        printf("%s已经被禁言\n",q[fd].id);
        strcpy(q[fd].buf,"你已被禁言");
        ret=send(fd,&q[fd],sizeof(q[fd]),0);
        if (ret == -1)
        {
            ERRLOG("send");
        }
        sqlite3_close(ppdb);  
        return 0;      
    }
    memset(sql,0,sizeof(sql));
    sprintf(sql,"select * from stu where id = '%s';",q[fd].destination);
    char **result1;
    int row1,column1;
    ret=sqlite3_get_table(ppdb,sql,&result1,&row1,&column1,NULL);
    if(ret!=SQLITE_OK)
    {
        printf("sqlite3_get_table:%s\n",sqlite3_errmsg(ppdb));
        return -1;
    }
    int i=0,j=0;
    int index=column1;
    for(i=0;i<row1;i++)
    {
        for(j=0;j<column1;j++)
        {
            printf(" %s=%s ",result1[j],result1[index]);
            index++;
        }
        putchar(10);
    }
        fd1=atoi(result1[11]);
        ret=send(fd1,&q[fd],sizeof(q[fd]),0);
        if (ret == -1)
        {
            ERRLOG("send");
        }
    ret = sqlite3_close(ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    return 0;
}
int qunfa(int fd)
{
    sqlite3 *ppdb;
    sqlite3 *ppdb1;
    int fd1;
    char sql[256]={0};
    char sql1[256]={0};
    int ret1 = sqlite3_open("record.db",&ppdb1); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb1)); 
    return -1;
    }
    memset(sql1,0,sizeof(sql1)); 
    sprintf(sql1,"insert into record values('%s','%s','%s');",q[fd].id,q[fd].destination,q[fd].buf);
    ret1=sqlite3_exec(ppdb1,sql1,NULL,NULL,NULL);
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
    int ret = sqlite3_open("stu.db",&ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    sprintf(sql,"select * from stu where id = %s;",q[fd].id);
    char **result;
    int row,column;
    ret=sqlite3_get_table(ppdb,sql,&result,&row,&column,NULL);
    if(ret!=SQLITE_OK)
    {
        printf("sqlite3_get_table:%s\n",sqlite3_errmsg(ppdb));
        return -1;
    }
    if(atoi(result[10])==1)
    {
        printf("%s已经被禁言\n",q[fd].id);
        strcpy(q[fd].buf,"你已被禁言");
        ret=send(fd,&q[fd],sizeof(q[fd]),0);
        if (ret == -1)
        {
            ERRLOG("send");
        }
        sqlite3_close(ppdb);  
        return 0;      
    }
    memset(sql,0,sizeof(sql));
    sprintf(sql,"select * from stu where state = 1 and id is not '%s';",q[fd].id);
    char **result1;
    int row1,column1;
    ret=sqlite3_get_table(ppdb,sql,&result1,&row1,&column1,NULL);
    if(ret!=SQLITE_OK)
    {
        printf("sqlite3_get_table:%s\n",sqlite3_errmsg(ppdb));
        return -1;
    }
    int i=0,j=0;
    int index=column1;
    for(i=0;i<row1;i++)
    {
        fd1=atoi(result1[11+6*i]);
        printf("%d ",fd1);
        ret=send(fd1,&q[fd],sizeof(q[fd]),0);
        if (ret == -1)
        {
            ERRLOG("send");
        }
        for(j=0;j<column1;j++)
        {
            printf(" %s=%s ",result1[j],result1[index]);
            index++;
        }
        putchar(10);
    }
    ret = sqlite3_close(ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    return 0;    
}
int wenjianin(int fd)
{
    sqlite3 *ppdb;
    int fd1;
    char sql[256]={0};
    int ret = sqlite3_open("stu.db",&ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    sprintf(sql,"select * from stu where id = '%s';",q[fd].destination);
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
        fd1=atoi(result[11]);
        q[fd].cmd=7;
        ret=send(fd1,&q[fd],sizeof(q[fd]),0);
        if (ret == -1)
        {
            ERRLOG("send");
        }   
    ret = sqlite3_close(ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    q[fd].cmd=6;
    strcpy(q[fd].destination,q[fd].buf);
    strcpy(q[fd].buf,"ready");
    printf("%s\n",q[fd].destination);
    printf("%s\n",q[fd].buf);
    ret=send(fd,&q[fd],sizeof(q[fd]),0);
    if (ret == -1)
    {
        ERRLOG("send");
    }
    FILE *fp = fopen(q[fd].destination,"w"); 
    if(NULL == fp) 
    { 
    perror("fopen"); 
    return -1; 
    }
    fclose(fp);
    return 0;
}
int wenjianout(int fd)
{
    sqlite3 *ppdb;
    int fd1;
    char sql[256]={0};
    int ret = sqlite3_open("stu.db",&ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    sprintf(sql,"select * from stu where id = '%s';",q[fd].destination);
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
        fd1=atoi(result[11]);
        q[fd].cmd=4;
        ret=send(fd1,&q[fd],sizeof(q[fd]),0);
        if (ret == -1)
        {
            ERRLOG("send");
        }   
    ret = sqlite3_close(ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    // q[fd].cmd=9;
    // strcpy(q[fd].destination,q[fd].buf);
    // strcpy(q[fd].buf,"ready");
    // printf("%s\n",q[fd].destination);
    // printf("%s\n",q[fd].buf);
    // ret=send(fd,&q[fd],sizeof(q[fd]),0);
    // if (ret == -1)
    // {
    //     ERRLOG("send");
    // }    

}
int upload(int fd,FILE *fp)
{

    if(strcmp(q[fd].buf,"结束")!=0)
    {
        printf("写入中\n");   
        if(fwrite(&q[fd].buf,sizeof(q[fd].buf),1,fp)==-1)
            {
                perror("fwrite");
            }         
        memset(q[fd].buf,0,N);
    }
    else
    printf("写入完成\n");      
}
int download(int fd)
{
    FILE *fp = fopen(q[fd].destination,"r"); 
    int m=0;
    if(NULL == fp) 
        { 
        perror("fopen"); 
        return -1; 
        }
        while(1)
        {
        printf("传输文件中.........\n");
        memset(q[fd].buf,0,N);
        m=fread(q[fd].buf,sizeof(q[fd].buf),1,fp);
        if(send(fd,&q[fd],sizeof(q[fd]),0)==-1)
        {
        ERRLOG("send error");
        }
        if(0 == m)
        { 
            if(feof(fp)) 
            { 
            printf("读到文件末尾\n"); 
            break; 
            }
            else 
            { 
            perror("fread"); 
            return -1; 
            } 
        }
        }
        fclose(fp);
        sleep(1);
        strcpy(q[fd].buf,"结束");
        if(send(fd,&q[fd],sizeof(q[fd]),0)==-1)
        {
            ERRLOG("send failed");
        }
        printf("下载完成\n");
}
int jinyan(int fd)
{
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
    if(strcmp(q[fd].buf,"禁言")==0)
    {
        memset(sql,0,sizeof(sql)); 
        sprintf(sql,"update stu set say =1 where id = '%s';",q[fd].destination);
        ret =sqlite3_exec(ppdb,sql,NULL,NULL,NULL);
        if(ret != SQLITE_OK)
        {
        printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
        return -1;
        }
    }
    if(strcmp(q[fd].buf,"解禁")==0)
    {
        memset(sql,0,sizeof(sql)); 
        sprintf(sql,"update stu set say =0 where id = '%s';",q[fd].destination);
        ret =sqlite3_exec(ppdb,sql,NULL,NULL,NULL);
        if(ret != SQLITE_OK)
        {
        printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb));
        return -1;
        }
    }
}