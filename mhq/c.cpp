#ifndef _C_H_
#define _C_H_

#include "c.h"
/*
 1.请求报文
	1.1 报头
		1B: 操作码 {0:请求文件列表,1:上传文件,2:下载文件,3:删除文件,4:重命名文件};
		
	1.2 报文
 2.返回状态及数据内容
*/

/*----------------------------获取文件大小------------------------------------------*/
unsigned long get_file_size(char *path)
{
	unsigned long filesize = -1;
	struct stat statbuff;
	if(stat(path, &statbuff) < 0){
		return filesize;
	}else{
		filesize = statbuff.st_size;
	}
	return filesize;
}
/*----------------------------获取文件名------------------------------------------*/
char *get_file_name(char *name)
{
	char *name_start = NULL;
	int sep = '/';
	if (NULL == name) {
			printf("the path name is NULL\n");
	    return NULL;
	}
	name_start = strrchr(name, sep);
 
	return (NULL == name_start)?name:(name_start + 1);
}

/*----------------------------建立套接口------------------------------------------*/
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
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //"127.0.0.1","34.92.193.74"
    return server_addr;
}

/*----------------------------获取文件列表------------------------------------------*/
int ProcessList(vector<string> &myList,string userName, string loginPassword)
{
    struct sockaddr_in server_addr = taojiekou();
    int sockfd,nbyte;
    char buf[N],*buff;
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
    
    string baowen = "0"+userName+loginPassword;//0用户名密码文件名
/*向服务端发送Get命令来获取文件，服务端返回文件是否存在*/
    buff = (char *)baowen.c_str();

    strcpy(buf,buff);
    cout<<buf<<endl;
    if(send(sockfd, buf, N, 0) < 0)
    {
        perror("Error: fail to send!\n");
		return -1;
    }

    bzero(buf,sizeof(buf));

    if(recv(sockfd, buf, N, 0) < 0)
    {
        perror("Error: fail to recv!\n");
		return -1;
    }
    if(buf[0] == '1')
    {
        bzero(buf,sizeof(buf));
        if(recv(sockfd,buf,N,0) < 0)
        {
            perror("Error: fail to recv!\n");
			return -1;
        }
        //cout<<buf<<endl;
    }
    int fileCount = *(int*)buf;
    cout<<"fileCount: "<<fileCount<<endl;
    bzero(buf,N);
    buf[0] = '1';
    if( send(sockfd, buf, N ,0) < 0 )
    {
        perror("Error1: fail to send!\n");
		return -1;
    }
    while(fileCount--){
        bzero(buf,N);
        if( recv(sockfd,buf,N,0) < 0)
        {
            perror("Error1: fail to recv!\n");
			return -1;
        }
        //cout<<"buf "<<buf<<endl;
        myList.push_back(buf);
        bzero(buf,N);
        buf[0] = '1';
        if( send(sockfd,buf,N,0) < 0)
        {
            perror("Error1: fail to send!\n");
			return -1;
        }
    }
    
    for (int i = 0; i < myList.size(); i++)
    {
        cout<<myList[i]<<endl;
    }
   
    close(sockfd);
    
    return 0; //successful

   
    
}

/*----------------------------上传文件------------------------------------------*/
int ProcessPut( char pathname[],string userName,string loginPassword)//上传文件
{
    //cout<<get_file_size(pathname)<<endl;
    struct sockaddr_in server_addr = taojiekou();
    int sockfd,fd,nbyte;
    char buf[N],*buff;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("fail to get\n");
        return -1;
    }
/*连接服务端*/
    if(connect(sockfd,(AS *)&server_addr,sizeof(server_addr)) < 0){
        printf("fail to connect server\n");
    }

    string baowen = "1"+userName+loginPassword;//1用户名登录密码
   
/*告知服务端要上传文件*/   
    buff = (char*)baowen.c_str();
    strcpy(buf,buff);

    send(sockfd,buf,N,0);
    bzero(buf,N);
    if(recv(sockfd,buf,N,0) < 0 )
    {
        perror("Error: fail to recv!\n");
        return -1;
    }
    int tot;
    if ((tot = get_file_size(pathname) )< 0)
        {
            perror("Error: fail to get file size!\n");
            return -1;
        }
    cout<<"tot:"<<tot<<endl;
    char *filenname;
    filenname = get_file_name(pathname);
    cout<<"filename:"<<filenname<<endl;
    
    
    if(buf[0] == '1')//确认成功
    {
        bzero(buf,N);
        *(int *)buf = tot;
        printf("%d\n",*(int*)buf);
        strcpy(&buf[4],filenname);
        //发送文件大小和文件名
        if(send(sockfd,buf,N,0)<0)
            {
                perror("Error: fail to send!\n");
                return -1;
            }
    }
    bzero(buf,N);
    if(recv(sockfd,buf,N,0) < 0)
    {
        perror("Error: fail to recv!\n");
        return -1;
    }
    FILE *fp;
    if(buf[0] == '1')
        fp=fopen(pathname,"rb");
    
    if(fp == NULL)
    {
        perror("Error: fail to open file!\n");
		return -1;
    }
    cout<<tot<<endl;
    while(tot)
    {
        cout<<"tot: "<<tot<<endl;
        int size = 0;
        bzero(buf,N);
        if(tot-MAX_BUF_SIZE >= 0)
        {
            size = MAX_BUF_SIZE;
            tot -= MAX_BUF_SIZE;
        }
        else
        {
            size = tot;
            tot = 0;
        }
        if(fread(buf,sizeof(char),size,fp) < size)
        {
            perror("Error: fail to read!\n");
            fclose(fp);
            return -1;
        }
        if(send(sockfd,buf,MAX_BUF_SIZE,0) < 0)
        {
            perror("Error: fail to send!\n");
			fclose(fp);
			return -1;
        }
        bzero(buf,MAX_BUF_SIZE);
        if(recv(sockfd,(void*)buf,MAX_BUF_SIZE,0) < 0)
        {
            perror("Error: fail to recv!\n");
			fclose(fp);
			return -1;
        }
        if(buf[0] != '1')break;
        
    }
    if(buf[0] != 1)
    {
        perror("Error: fail to upload!\n");
		fclose(fp);
        close(sockfd);
        return -1;
    }
    else
    {
        printf("Put file successfully!\n");
        fclose(fp);
        close(sockfd);
        return 0;
    }
 
}

/*----------------------------下载文件------------------------------------------*/
int ProcessGet(char pathname[],string userName,string loginPassword)//2下载文件
{
    
    struct sockaddr_in server_addr = taojiekou();
    int sockfd,fd,nbyte;
    char buf[N],*buff;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("fail to get\n");
        return -1;
    }
/*连接服务端*/
    if(connect(sockfd,(AS *)&server_addr,sizeof(server_addr)) < 0){
        printf("fail to connect server\n");
    }

    string baowen = "2"+userName+loginPassword;//2用户名登录密码
   
/*告知服务端要下载文件*/   
    buff = (char*)baowen.c_str();
    strcpy(buf,buff);

    send(sockfd,buf,N,0);
    bzero(buf,N);
    if(recv(sockfd,buf,N,0) < 0 )
    {
        perror("Error: fail to recv!\n");
        return -1;
    }
    if(buf[0] == '1')//接受确认
    {
        //报文第一次发送：文件名  
        // char filename[1024];
        // filename = pathname;
        cout<<"filename:"<<pathname<<endl;
        strcpy(buf,pathname);
        if(send(sockfd,buf,N,0) < 0)
        {
             perror("Error: fail to send!\n");
             return -1;
        }   
    }
    bzero(buf,N);
    //接受文件大小
    if(recv(sockfd,buf,N,0) < 0)
    {
        perror("Error: fail to recv!\n");
        return -1;
    }
    int tot = *(int*)buf;
    char downloadPath[1024] = ADDR_ST;
    strcat(downloadPath,pathname);
    FILE *fp = fopen(downloadPath,"wb");
    if(fp == NULL)
    {
        perror("Error: fail to open file!\n");
		return -1;
    }
    while(tot)
    {
        cout<<"tot: "<<tot<<endl;
        int size = 0;
        bzero(buf,N);
        if(recv(sockfd,buf,N,0) < 0 )
        {
            perror("Error: fail to recv!\n");
			return -1;
        }
        if(tot-MAX_BUF_SIZE >= 0)
        {
            size=MAX_BUF_SIZE;
			tot-=MAX_BUF_SIZE;
        }
        else
        {
            size=tot;
			tot=0;    
        }
        if(fwrite(buf,sizeof(char),size,fp)<size)
			{
				perror("Error: fail to write!\n");
				fclose(fp);
				return -1;
			}
			bzero(buf,MAX_BUF_SIZE);
			buf[0]='1';
			if(send(sockfd,buf,MAX_BUF_SIZE,0)<0)
			{
				perror("Error: fail to send!\n");
				fclose(fp);
				return -1;
			}
        
    }
   
    printf("Get file successfully!\n");
    fclose(fp);
    close(sockfd);

    return 0;
}


/*----------------------------删除文件------------------------------------------*/
int ProcessDelete(char filename[],string userName, string loginPassword)
{
    struct sockaddr_in server_addr = taojiekou();
    int sockfd,nbyte,fd;
    char buf[N],*buff;
   
    if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0){
        printf("fail\n");
        return -1;
    }
/*连接服务端*/
    if(connect(sockfd,(AS *)&server_addr,sizeof(server_addr)) < 0){
        printf("fail to connect server\n");
        return -1;
    }
    
    string baowen = "3"+userName+loginPassword;//3用户名登录密码
/*向服务端发送Get命令来获取文件，服务端返回文件是否存在*/
    buff = (char *)baowen.c_str();
    strcpy(buf,buff);

    if(send(sockfd, buf, N, 0) < 0)
    {
        perror("Error: fail to send!\n");
		return -1;
    }
    bzero(buf,N);
    if(recv(sockfd,buf,N,0) < 0)
    {
        perror("Error: fail to recv!\n");
		return -1;
    }
    if(buf[0] == '1')
    {
        //报文第一次发送文件名
        bzero(buf,N);
        strcpy(buf,filename);
        cout<<"fliename to send:"<<buf<<endl;
        if(send(sockfd,buf,N,0) < 0)
        {
            perror("Error: fail to send!\n");
			return -1;
        }
    }
    bzero(buf,N);
    //接受确认
    if(recv(sockfd,buf,N,0) < 0)
    {
        perror("Error: fail to send!\n");
		return -1;
    }
    if(buf[0] == '1')
    {
        printf("Delete file successfully!\n");
        close(sockfd);
        return 0;
    }
    if(buf[0] != '1')
    {
        perror("Error: fail to remove file!\n");
        close(sockfd);
        return -1;
    }

}

/*----------------------------重命名文件------------------------------------------*/
int ProcessRename(char filename[],char newfilename[],string userName,string loginPassword)
{
    struct sockaddr_in server_addr = taojiekou();
    int sockfd,nbyte,fd;
    char buf[N],*buff;
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
    string baowen = "4"+userName+loginPassword;//4用户名登录密码
/*向服务端发送Get命令来获取文件，服务端返回文件是否存在*/
    buff = (char *)baowen.c_str();
    strcpy(buf,buff);

    if(send(sockfd, buf, N, 0) < 0)
    {
        perror("Error: fail to send!\n");
		return -1;
    }
    bzero(buf,N);
    if(recv(sockfd,buf,N,0) < 0)
    {
        perror("Error: fail to recv!\n");
		return -1;
    }
    if(buf[0] == '1')
    {
        //报文第一次发送文件名
        bzero(buf,N);
        strcpy(buf,filename);
        cout<<"fliename to send:"<<buf<<endl;
        if(send(sockfd,buf,N,0) < 0)
        {
            perror("Error: fail to send!\n");
			return -1;
        }
    }
    bzero(buf,N);
    //接受确认
    if(recv(sockfd,buf,N,0) < 0)
    {
        perror("Error: fail to send!\n");
		return -1;
    }
    if(buf[0] == '1')
    {
        //报文第二次发送要修改的文件名
        bzero(buf,N);
        strcpy(buf,newfilename);
        cout<<"fliename to modify:"<<buf<<endl;
        if(send(sockfd,buf,N,0) < 0)
        {
            perror("Error: fail to send!\n");
			return -1;
        }

    }
    bzero(buf,N);
    if(recv(sockfd,buf,N,0) < 0)
    {
        perror("Error: fail to send!\n");
		return -1;
    }
    if(buf[0] == '1')
    {
        printf("Rename file successfully!\n");
        close(sockfd);
        return 0;
    }
    if(buf[0] != '1')
    {
        perror("Error: fail to remove file!\n");
        close(sockfd);
        return -1;
    }
    return 0;
}

/*----------------------------打印帮助------------------------------------------*/
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
 
#endif





