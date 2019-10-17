#ifndef _BDCLOUD_LIB_H_
#define _BDCLOUD_LIB_H_
#include "bdCloud_Lib.h"

/*----------------------------��ͷ��Ӧ------------------------------------------*/

int recv_header(const int sock_fd,char *buf,int *auth)
{
	if(recv(sock_fd,(void*)buf,MAX_BUF_SIZE,0) < 0)
	{
		perror("Error: fail to recv!\n");
		return -1;
	}
	else
	{
		*auth=((buf[1]=='A')?1:0);
		if(*auth==1)
		{
			if(strncmp(&buf[2],ADMIN_PSD,PSD_LEN)==0)
			{
				return (int)(buf[0]-'0');
			}
			else
			{
				*auth=-1;
				return INFINITE;
			}
		}
		else
		{
			if(strncmp(&buf[2],USER_PSD,PSD_LEN)==0)
			{
				return (int)(buf[0]-'0');
			}
			else
			{
				*auth=-1;
				return INFINITE;
			}
		}
	}
}

/*----------------------------Ŀ¼��Ӧ------------------------------------------*/
int recv_dir(const int sock_fd,char *buf,const int auth)
{
	if(auth!=-1)
	{
		DIR *dir;
		int cnt=0;
		struct dirent *file;
		dir=opendir(ADDR_ST);
		if(dir==NULL)
		{
			perror("Error: fail to open directory!\n");
			return -1;
		}
		while(file=readdir(dir))
		{
			if(strcmp(file->d_name,".") == 0 || strcmp(file->d_name,"..") == 0)
  			{
   				continue;
  			}
  			if(file->d_type == DT_REG)   cnt++;
		}
		closedir(dir);
		*(int*)buf=cnt;
		if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
		{
			perror("Error: fail to send!\n");
			return -1;
		}
		bzero(buf,sizeof(buf));
		dir=opendir(ADDR_ST);
		if(dir==NULL)
		{
			perror("Error: fail to open directory!\n");
			return -1;
		}
		if(recv(sock_fd,buf,MAX_BUF_SIZE,0)<0)
		{
			perror("Error: fail to recv!\n");
			return -1;
		}
		if(buf[0]=='1')
		{
			while(file=readdir(dir))
			{
				bzero(buf,sizeof(buf));
				if(strcmp(file->d_name,".") == 0 || strcmp(file->d_name,"..") == 0)
  				{
   					continue;
  				}
  				if(file->d_type == DT_REG){
  					bcopy(file->d_name,buf,file->d_reclen);
  					if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
					{
						perror("Error: fail to send!\n");
						return -1;
					}
					bzero(buf,sizeof(buf));
					if(recv(sock_fd,buf,MAX_BUF_SIZE,0)<0)
					{
						perror("Error: fail to recv!\n");
						return -1;
					}
					if(buf[0]!='1') break;
				}
			}
			closedir(dir);
		}
		return 0;
	}
}

/*----------------------------�ϴ���Ӧ------------------------------------------*/
int recv_upload(const int sock_fd,char *buf,const int auth)
{

}

/*----------------------------������Ӧ------------------------------------------*/
int recv_download(const int sock_fd,char *buf,const int auth)
{

}

/*----------------------------ɾ����Ӧ------------------------------------------*/
int recv_del(const int sock_fd,char *buf,const int auth)
{

}

/*----------------------------�޸���Ӧ------------------------------------------*/
int recv_update(const int sock_fd,char *buf,const int auth)
{

}

/*----------------------------�ײ㺯��------------------------------------------*/
unsigned long get_file_size(const char *path)
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

#endif
