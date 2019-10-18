#include "client.h"
#include <QDebug>
using namespace std;







struct sockaddr_in taojiekou()
{
    int sockfd;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        printf("fail to socket ");

        }
    /*服务端信息*/
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = inet_addr("34.92.193.74");
    return server_addr;
}

int ProcessList(std::vector<string> &myList,string userName, string loginPassword)
{
    struct sockaddr_in server_addr = taojiekou();
    int sockfd,nbyte,fd;
    char buf[N],*buff;
    //ip
    if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0){
        printf("fail\n");
        qDebug()<<"fail1"<<endl;
        return -1;
    }
/*连接服务端*/
    if(connect(sockfd,(AS *)&server_addr,sizeof(server_addr)) < 0){
        printf("fail to connect server\n");
        qDebug()<<"fail2"<<endl;
        return -1;
    }

    string baowen = "0"+userName+loginPassword;//0用户名密码文件名
/*向服务端发送Get命令来获取文件，服务端返回文件是否存在*/
    buff = (char *)baowen.c_str();

    strcpy(buf,buff);

    send(sockfd, buf, N, 0);

    bzero(buf,sizeof(buf));

    recv(sockfd, buf, N, 0);

    int fileCount = *(int*)buf;

    while(fileCount--){
        bzero(buf,N);
        strcpy(buf,"1");
        if( send(sockfd, buf, N ,0) < 0 )
        {
            perror("Error1: fail to send!\n");
            qDebug()<<"fail3"<<endl;
            return -1;
        }
        bzero(buf,N);
        if( recv(sockfd,buf,N,0) < 0)
        {
            perror("Error1: fail to recv!\n");
            qDebug()<<"fail4"<<endl;
            return -1;
        }

        myList.push_back(buf);
    }

    for (int i = 0; i < myList.size(); i++)
    {
        cout<<myList[i]<<endl;
    }
    close(fd);
    close(sockfd);

    return 0; //successful



}

int ProcessDelete(string command,string userName, string loginPassword)
{
    struct sockaddr_in server_addr = taojiekou();
    int sockfd,nbyte,fd;
    char *buf;

    if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0){
        printf("fail\n");
        return -1;
    }
/*连接服务端*/
    if(connect(sockfd,(AS *)&server_addr,sizeof(server_addr)) < 0){
        printf("fail to connect server\n");
        return -1;
    }

    string baowen = "3"+userName+loginPassword+command;//3用户名登录密码文件名
/*向服务端发送Get命令来获取文件，服务端返回文件是否存在*/
    buf = (char *)baowen.c_str();
    send(sockfd, buf, N, 0);

    printf("Delete file successfully!\n");
    close(fd);
    close(sockfd);
    return 0;
}

int ProcessRename(string command,string userName,string loginPassword)
{
    struct sockaddr_in server_addr = taojiekou();
    int sockfd,nbyte,fd;
    char *buf;
    //ip
    if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0){
        printf("fail\n");
        return -1;
    }
/*连接服务端*/
    if(connect(sockfd,(AS *)&server_addr,sizeof(server_addr)) < 0){
        printf("fail to connect server\n");
        return -1;
    }
    string baowen = "4"+userName+loginPassword+command;//4用户名登录密码文件名
/*向服务端发送Get命令来获取文件，服务端返回文件是否存在*/
    buf = (char *)baowen.c_str();

    send(sockfd, buf, N, 0);

    printf("Rename file successfully!\n");
    close(fd);
    close(sockfd);
    return 1;
}


void PrintHelp()
{
    printf("help : display help info\n");
    printf("List ：request file list\n");
    printf("get  : get <filename>\n");
    printf("put  : put <filename>\n");
    printf("rename  : rename file\n");
    printf("delete  : delete file\n");
    printf("quit : quit the client\n");
}

int ProcessGet(string command,string userName,string loginPassword)
{
    struct sockaddr_in server_addr = taojiekou();
    int sockfd,nbyte,fd;

    //ip
    if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0){
        printf("fail\n");
        return -1;
    }
/*连接服务端*/
    if(connect(sockfd,(AS *)&server_addr,sizeof(server_addr)) < 0){
        printf("fail to connect server\n");
        return -1;
    }

    string baowen = "1"+userName+loginPassword+command;//1用户名登录密码文件名
    /*向服务端发送Get命令来获取文件，服务端返回文件是否存在*/
    char *buf = (char *)baowen.c_str();

    send(sockfd, buf, N, 0);
    recv(sockfd, buf, N, 0);
/*服务端无此文件*/
    if (buf[0] == 'N') {
        printf("No such file on server\n");
        return -1;
    }
/*mode设为0666，赋予可读可写权限*/
    char *openCommand = (char *)command.c_str();
    if((fd = open(openCommand,O_WRONLY|O_CREAT|O_TRUNC,0666)) < 0){
        printf("fail to create local file %s\n",openCommand);
        return -1;
    }

    while((nbyte = recv(sockfd,buf,N,0)) > 0){
        write(fd,buf,nbyte);
    }
    printf("Get file successfully!\n");
    close(fd);
    close(sockfd);
    return 1;
}

int ProcessPut(string command,string userName,string loginPassword)
{
    struct sockaddr_in server_addr = taojiekou();
   // char command[]
    int sockfd,fd,nbyte;
    char *buf;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("fail to get\n");
        return -1;
    }
/*连接服务端*/
    if(connect(sockfd,(AS *)&server_addr,sizeof(server_addr)) < 0){
        printf("fail to connect server\n");
    }
/*打开文件*/
    char *openCommand = (char *)command.c_str();
    if((fd = open(openCommand,O_RDONLY)) < 0){
        printf("fail to open %s\n",openCommand);
        return -1;
    }
    string baowen = "2"+userName+loginPassword+command;
    //sprintf(buf,"2%s%s%s",userName,loginPassword,command);//2用户名登录密码文件名
    //printf("%s\n",buf);
/*告知服务端要上传文件*/
    buf = (char*)baowen.c_str();
    send(sockfd,buf,N,0);

    while ((nbyte = read(fd,buf,N)) > 0){
        send(sockfd,buf,nbyte, 0);
    }

    printf("Put file successfully!\n");

    close(fd);
    close(sockfd);
    return 1;
}





