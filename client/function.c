#include "function.h"
void menu1()
{   
    system("clear");
    printf("\t\t****聊天室****\t\t\n");
    printf("\t\t****1.登录****\t\t\n");
    printf("\t\t****2.注册****\t\t\n");
    printf("\t\t****3.退出****\t\t\n");
}
void menuusr()
{
    printf("\t\t****1.群发消息****\t\t\n");//快捷消息或手动消息
    printf("\t\t****2.私发消息****\t\t\n");
    printf("\t\t****3.查看在线人员****\t\t\n");
    printf("\t\t****4.发送文件****\t\t\n");
    printf("\t\t****5.接收文件****\t\t\n");
    printf("\t\t****6.查看本地消息记录****\t\t\n");
    printf("\t\t****7.退出聊天室****\t\t\n");       
}
void menusuper()
{
    printf("\t\t****1.群发消息****\t\t\n");//快捷消息或手动消息
    printf("\t\t****2.私发消息****\t\t\n");
    printf("\t\t****3.查看在线人员****\t\t\n");
    printf("\t\t****4.禁言用户****\t\t\n");
    printf("\t\t****5.踢出用户****\t\t\n");
    printf("\t\t****6.更改其他用户权限****\t\t\n");
    printf("\t\t****7.退出聊天室****\t\t\n");   
}
void *Myfun(void *m)
{
    sqlite3 *ppdb2;
    char sql1[256]={0};
    int ret1;
    while(1)
    {
    if(recv(sockfd,&q1,sizeof(q1),0)==-1)
    {
        ERRLOG("send failed");
    }
    ret1 = sqlite3_open("record.db",&ppdb2); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb2)); 
    }
    memset(sql1,0,sizeof(sql1)); 
    sprintf(sql1,"insert into record values('%s','%s','%s');",q1.id,q1.destination,q1.buf);
    ret1=sqlite3_exec(ppdb2,sql1,NULL,NULL,NULL);
    if(ret1 != SQLITE_OK)
    {
        printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb2));
    }
    ret1 = sqlite3_close(ppdb2); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb2)); 
    }
    if(strcmp(q1.id,q.id)!=0)
    {
        if(q1.cmd==7)
        {
            printf("%s想要向您传送文件%s\n",q1.id,q1.buf);
            qq[o]=q1;
            o++;
        }
        else
        {
        strcat(q1.buf,"\n");
        printf("%s发来了%s",q1.id,q1.buf);
        }
    }
    else if(q1.cmd ==6)
    {
        strcat(q1.buf,"\n");
        printf("服务器:%s",q1.buf);
        if(strcmp(q1.buf,"ready\n")==0)
        {
            wenjianout2();
        }
    }
    else if(q1.cmd ==9)
    {
        printf("服务器:%s\n",q1.buf);
        FILE *fp = fopen(q1.destination,"a"); 
        if(NULL == fp) 
        { 
            perror("fopen"); 
            exit(1); 
        }
        wenjianin2(fp);
        fclose(fp);     
    }
    else
    {
    strcat(q1.buf,"\n");
    printf("服务器:%s",q1.buf);
    }
    }
}
int sifa()
{
    sqlite3 *ppdb3;
    char sql1[256]={0};
    int ret1;
    system("clear");
    char a='0'; 
    char duixiang[32]={0};
    char xiaoxi[32]={0};
    int id=0,state=0;
    q.cmd=4;
    ret1 = sqlite3_open("record.db",&ppdb3); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb3)); 
    return -1;
    }
    printf("请输入");
    printf("\t\t****发送对象****\t\t\n");
    gets(duixiang); 
    strcpy(q.destination,duixiang);
    printf("请输入");
    printf("\t\t****消息内容****\t\t\n");
    gets(xiaoxi);
    strcpy(q.buf,xiaoxi);
    if(send(sockfd,&q,sizeof(q),0)==-1)
    {
        ERRLOG("send failed");
    }
    memset(sql1,0,sizeof(sql1)); 
    sprintf(sql1,"insert into record values('%s','%s','%s');",q.id,q.destination,q.buf);
    ret1=sqlite3_exec(ppdb3,sql1,NULL,NULL,NULL);
    if(ret1 != SQLITE_OK)
    {
        printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb3));
        return -1;
    }
    ret1 = sqlite3_close(ppdb3); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb3)); 
    return -1;
    }
}
int qunfa()
{
    sqlite3 *ppdb4;
    char sql1[256]={0};
    int ret1;
    system("clear");
    char a='0'; 
    char xiaoxi[32]={0};
    int id=0,state=0;
    q.cmd=5; 
    strcpy(q.destination,"all");
    ret1 = sqlite3_open("record.db",&ppdb4); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb4)); 
    return -1;
    }
    printf("请输入");
    printf("\t\t****消息内容****\t\t\n");
    gets(xiaoxi);
    strcpy(q.buf,xiaoxi);
    if(send(sockfd,&q,sizeof(q),0)==-1)
    {
        ERRLOG("send failed");
    }
    memset(sql1,0,sizeof(sql1)); 
    sprintf(sql1,"insert into record values('%s','%s','%s');",q.id,q.destination,q.buf);
    ret1=sqlite3_exec(ppdb4,sql1,NULL,NULL,NULL);
    if(ret1 != SQLITE_OK)
    {
        printf("sqlite3_exec:%s\n",sqlite3_errmsg(ppdb4));
        return -1;
    }
    ret1 = sqlite3_close(ppdb4); 
    if(ret1 != SQLITE_OK) 
    { 
    printf("sqlite3_close:%s\n",sqlite3_errmsg(ppdb4)); 
    return -1;
    }
}
int wenjianin1()
{
        system("clear");
        printf("\t\t****待接收文件****\t\t\n");
        int i=0;
        for(i=0;i<=o-1;i++)
        {
            printf("%d.%s\n",i+1,qq[i].buf);
        }
        int a,b;
        char tmp[32];
        scanf("%d",&a);
        a=a-1;
        printf("\t\t****1.同意接收****\t\t\n");
        printf("\t\t****2.拒绝接收****\t\t\n");
        scanf("%d", &b);
        while ((ch = getchar()) != EOF && ch != '\n');
        strcpy(tmp,qq[a].destination);
        strcpy(qq[a].destination,qq[a].id);
        strcpy(qq[a].id,tmp);
        if(b == 1)
        {
            printf("您选择同意接收文件%s\n",qq[a].buf);
            FILE *fp = fopen(qq[a].buf,"w"); 
            if(NULL == fp) 
            { 
            perror("fopen"); 
            return -1; 
            }
            fclose(fp);
            qq[a].cmd=9;
            strcpy(qq[a].destination,qq[a].buf);
            if(send(sockfd,&qq[a],sizeof(qq[a]),0)==-1)
        {
            ERRLOG("send failed");
        }
        }
        if(b == 2)
        {
            printf("您选择拒绝接收文件%s\n",qq[a].buf);
            strcat(qq[a].buf,"被拒绝接收");
            qq[a].cmd=4;
            if(send(sockfd,&qq[a],sizeof(qq[a]),0)==-1)
        {
            ERRLOG("send failed");
        }
        }
        return 0;
}
int wenjianin2(FILE *fp)
{
    system("clear");
    printf("文件名=%s\n",q1.destination);
    q=q1;
    if(strcmp(q.buf,"结束")!=0)
    {
        printf("写入中\n");   
        if(fwrite(&q.buf,sizeof(q.buf),1,fp)==-1)
            {
                perror("fwrite");
            }         
        memset(q.buf,0,N);
    }
    else
    printf("写入完成\n");  
    menuusr();  
}
int wenjianout1()
{
    system("clear");
    char a='0';
    char duixiang[32]={0}; 
    char wjname[32]={0};
    int id=0,state=0;
    q.cmd=6; 
    printf("请输入");
    printf("\t\t****发送对象****\t\t\n");
    gets(duixiang); 
    strcpy(q.destination,duixiang);
    printf("请输入");
    printf("\t\t****文件名****\t\t\n");
    gets(wjname);
    strcpy(q.buf,wjname);
    if(send(sockfd,&q,sizeof(q),0)==-1)
    {
        ERRLOG("send failed");
    }


}
int wenjianout2()
{
    system("clear");
    printf("文件名=%s\n",q1.destination);
    q=q1;
    q.cmd=8;
    FILE *fp = fopen(q.destination,"r"); 
    int m=0;
    if(NULL == fp) 
        { 
        perror("fopen"); 
        return -1; 
        }
        while(1)
        {
        printf("上传文件中.........\n");
        memset(q.buf,0,N);
        m=fread(q.buf,sizeof(q.buf),1,fp);
        if(send(sockfd,&q,sizeof(q),0)==-1)
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
        strcpy(q.buf,"结束");
        if(send(sockfd,&q,sizeof(q),0)==-1)
        {
            ERRLOG("send failed");
        }
        printf("上传完成\n");
        menuusr();
}
void look()
{
    char a='0'; 
    char ID[32]={0};
    char pass[16]={0};
    int id=0,state=0;
    q.cmd=3;
    strcpy(q.destination,"0");
    if(send(sockfd,&q,sizeof(q),0)==-1)
    {
        ERRLOG("send failed");
    }
}
int jinyan()
{
    int a=0; 
    char ID[32]={0};
    q.cmd=10;
    printf("请输入");
    printf("\t\t****被修改发言权限的ID****\t\t\n");
    gets(ID);
    strcpy(q.destination,ID);     
    printf("请选择");
    printf("\t\t****1.禁言此ID****\t\t\n");
    printf("\t\t****2.解禁此ID****\t\t\n");   
    scanf("%d",&a);
    while ((ch = getchar()) != EOF && ch != '\n');
    if(a==1)
    {
        strcpy(q.buf,"禁言");
    }
    if(a==2)
    {
        strcpy(q.buf,"解禁");
    }
    if(send(sockfd,&q,sizeof(q),0)==-1)
    {
        ERRLOG("send failed");
    }    
}
int tiren()
{
    ;
}
int power()
{
    ;
}
int login()
{
    system("clear");
    char a='0'; 
    char ID[32]={0};
    char pass[16]={0};
    int id=0,state=0;
    sqlite3 *ppdb1;
    char sql1[256]={0};
    q.cmd=1;
    strcpy(q.destination,"0");
ONE:
    printf("请输入");
    printf("\t\t****你的ID****\t\t\n");
    gets(ID);
    strcpy(q.id,ID); 
    printf("请输入");
    printf("\t\t****你的密码****\t\t\n");
    gets(pass);
    strcpy(q.buf,pass);
    if(send(sockfd,&q,sizeof(q),0)==-1)
    {
        ERRLOG("send failed");
    }
    if(recv(sockfd,&q,sizeof(q),0)==-1)
    {
        ERRLOG("send failed");
    }
    printf("%s",q.buf);
    if(strcmp(q.buf,"登录成功\n")==0)
    {    
        pthread_t tid=0;
        if(pthread_create(&tid,NULL,Myfun,NULL)!=0)
        {
            printf("Error\n");
            return -1;
        }
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
        if(strcmp(q.id,"root")==0)
        {
        while(1)
        {
        menusuper();
        char y=0;
        y=getchar();
        while ((ch = getchar()) != EOF && ch != '\n');
        switch (y)
        {
        case 49:
        qunfa();
        break;
        case 50:
        sifa();
        break;
        case 51:
        look();
        break;
        case 52:
        jinyan();
        break;
        case 53:
        tiren();
        break;
        case 54:
        power();
        break;
        case 55:
        exit(0);
        default:
        printf("错误输入,请重新输入\n");
        break;
        }
        }
        }
        else 
        {
        while(1)
        {
        menuusr();
        char x=0;
        x=getchar();
        while ((ch = getchar()) != EOF && ch != '\n');
        switch (x)
        {
        case 49:
        qunfa();
        break;
        case 50:
        sifa();
        break;
        case 51:
        look();
        break;
        case 52:
        wenjianout1();
        break;
        case 53:
        wenjianin1();
        break;
        case 54:
        record();
        break;
        case 55:
        exit(0);
        default:
        printf("错误输入,请重新输入\n");
        break;
        }
        }
        }
    }
    else if(strcmp(q.buf,"已登录\n")==0)
    {
        printf("请重新输入账号密码\n");
        goto ONE;
    }

    return 0;
}
int enroll()
{
    system("clear");
    char a='0'; 
    char ID[32]={0};
    char pass[16]={0};
    int id=0,state=0;
    q.cmd=2;
    strcpy(q.destination,"0");
TWO:
    printf("请输入");
    printf("\t\t****你注册的ID****\t\t\n");
    gets(ID);
    strcpy(q.id,ID); 
    printf("请输入");
    printf("\t\t****你的密码****\t\t\n");
    gets(pass);
    strcpy(q.buf,pass);
    if(send(sockfd,&q,sizeof(q),0)==-1)
    {
        ERRLOG("send failed");
    }
    if(recv(sockfd,&q,sizeof(q),0)==-1)
    {
        ERRLOG("send failed");
    }
    if(strcmp(q.buf,"注册成功\n")==0)
    {    
        printf("注册成功\n");
        sleep(1);
    }
    else if(strcmp(q.buf,"已注册\n")==0)
    {
        printf("请重新输入账号密码\n");
        goto TWO;
    }
    return 0;
}
int record()
{
    sqlite3 *ppdb;
    char sql[256]={0};
    int ret = sqlite3_open("record.db",&ppdb); 
    if(ret != SQLITE_OK) 
    { 
    printf("sqlite3_open:%s\n",sqlite3_errmsg(ppdb)); 
    return -1;
    }
    sprintf(sql,"select * from record;");
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
    memset(q.buf,0,sizeof(q.buf));
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
