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
    printf("bdCloud_Server is running.\n");
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
			bzero(buf,sizeof(buf));
			switch (recv_header(sock_fd,buf,&auth))
			{
				case 0:{
					recv_dir(sock_fd,buf,auth);
					break;
				}
				case 1:{
					recv_upload(sock_fd,buf,auth);
					break;
				}
				case 2:{
					recv_download(sock_fd,buf,auth);
					break;
				}
				case 3:{
					recv_del(sock_fd,buf,auth);
					break;
				}
				case 4:{
					recv_update(sock_fd,buf,auth);
					break;
				}
				case -1:{
					break;
				}
				default:{
					buf[0]='0';
					if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
					{
						perror("Error: fail to send!\n");
					}
					break;
				}
			}

			/*
			if((recvbytes = recv(sock_fd, buf, 1024, 0)) < 0)
			{
		        fprintf(stderr, "recv error:%s\n", strerror(errno));
			    exit(1);
			}
            buf[recvbytes] = '\0';
            printf("buf is %s\n", buf);
			close(sockfd);
			close(sock_fd);
		    exit(0);
		    */
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
