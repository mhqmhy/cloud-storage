#include"bdCloud_Lib.h"

int main()
{
    int sockfd;
    int sock_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int addrlen = sizeof(struct sockaddr);
    socklen_t addrinlen = sizeof(struct sockaddr_in);
    int recvbytes;
    char buf[MAX_BUF_SIZE];
    //�����������׽���
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error: fail to create socket!\n") ;
		exit(1);
    }
    //���������sockaddr�ṹ
    bzero(&server_addr, addrinlen);
    server_addr.sin_family = AF_INET;
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY��ʾ���Խ�������IP��ַ�����ݣ��������е�IP
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//���ڰ󶨵�һ���̶���IP��inet_addr���ڰ����ּӸ�ʽ��IPת��Ϊ����IP
    server_addr.sin_port = htons(PORT);
    //��socket��IP��ַ
    if(bind(sockfd, (struct sockaddr *)&server_addr, addrlen) < 0)
    {
        perror("Error: fail to bind!\n");
		exit(1);
    }

    //�����������ӵ����ͻ�����Ŀ
    if(listen(sockfd, MAX_CONNECT) < 0)
    {
        perror("Error: fail to listen!\n");
		exit(1);
    }
    printf("bdCloud_Server is running...\n");
    while(1)
    {
        //��������
		if((sock_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addrinlen)) < 0)
		{
            perror("Error: fail to accept!\n");
			exit(1);
		}
		else
		{
			printf("%s is connected!\n",inet_ntoa(client_addr.sin_addr));
		}
		if(fork() == 0)
		{
			int auth=-1;
			bzero(buf,MAX_BUF_SIZE);
			switch (recv_header(sock_fd,buf,&auth))
			{
				case 0:{
					bzero(buf,MAX_BUF_SIZE);
					buf[0]='1';
					if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
					{
						perror("Error: fail to send!\n");
						break;
					}
					recv_dir(sock_fd,buf,auth);
					break;
				}
				case 1:{
					bzero(buf,MAX_BUF_SIZE);
					buf[0]='1';
					if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
					{
						perror("Error: fail to send!\n");
						break;
					}
					if(recv_upload(sock_fd,buf,auth)==1)
					{
						bzero(buf,MAX_BUF_SIZE);
						buf[0]='0';
						if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
						{
							perror("Error: fail to send!\n");
						}
					}
					break;
				}
				case 2:{
					bzero(buf,MAX_BUF_SIZE);
					buf[0]='1';
					if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
					{
						perror("Error: fail to send!\n");
						break;
					}
					recv_download(sock_fd,buf,auth);
					break;
				}
				case 3:{
					bzero(buf,MAX_BUF_SIZE);
					buf[0]='1';
					if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
					{
						perror("Error: fail to send!\n");
						break;
					}
					int judge=recv_del(sock_fd,buf,auth);
					if(judge!=-1)
					{
						bzero(buf,MAX_BUF_SIZE);
						buf[0]=(judge==0)?'1':'0';
						if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
						{
							perror("Error: fail to send!\n");
						}
					}
					break;
				}
				case 4:{
					bzero(buf,MAX_BUF_SIZE);
					buf[0]='1';
					if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
					{
						perror("Error: fail to send!\n");
						break;
					}
					int judge=recv_modify(sock_fd,buf,auth);
					if(judge!=-1)
					{
						bzero(buf,MAX_BUF_SIZE);
						buf[0]=(judge==0)?'1':'0';
						if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
						{
							perror("Error: fail to send!\n");
						}
					}
					break;
				}
				default:{
					bzero(buf,MAX_BUF_SIZE);
					buf[0]='0';
					if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
					{
						perror("Error: fail to send!\n");
					}
					break;
				}
			}
			printf("Finish the task from %s !\n",inet_ntoa(client_addr.sin_addr));
		    close(sockfd);
			close(sock_fd);
		    exit(0);
		}
		else
		{
		    //ͨѶ����
	        close(sock_fd);
	    }
	}
		//�ر�
	close(sockfd);
    return 0;
}
