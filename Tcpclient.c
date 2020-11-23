#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
 
#define  PORT 1234
#define  MAXDATASIZE 1024
 
int main(int argc, char *argv[])
{
       int  sockfd, num;
       char  buf[MAXDATASIZE];
       struct hostent *he;
       struct sockaddr_in server;
       if (argc!=2) {
              printf("Usage:%s <IP Address>\n",argv[0]);
              exit(1);
       }
       if((he=gethostbyname(argv[1]))==NULL){
              printf("gethostbyname()error\n");
              exit(1);
       }
       if((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1){
              printf("socket()error\n");
              exit(1);
       }
       bzero(&server,sizeof(server));
       server.sin_family= AF_INET;
       server.sin_port = htons(PORT);
       server.sin_addr =*((struct in_addr *)he->h_addr);
       if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))==-1){
              printf("connect()error\n");
              exit(1);
       }
       
       memset(buf, '\0', sizeof(buf));
       printf("please input char :\n");
       //fgets它的功能是从 stream 流中读取 size 个字符存储到字符指针变量 s 所指向的内存空间。
       fgets(buf,1024,stdin);
       send(sockfd,buf,strlen(buf),0);
       if((num=recv(sockfd,buf,MAXDATASIZE,0)) == -1){
              printf("recv() error\n");
              exit(1);
       }
       buf[num]='\0';
       printf("Server Message: %s\n",buf);
       
       close(sockfd);
       return 0;
}
