#ifndef _BDCLOUD_LIB_H_
#define _BDCLOUD_LIB_H_
#include "bdCloud_Lib.h"

/*----------------------------报头响应------------------------------------------*/

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

/*----------------------------目录响应------------------------------------------*/
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
		bzero(buf,MAX_BUF_SIZE);
		*(int*)buf=cnt;
		if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
		{
			perror("Error: fail to send!\n");
			return -1;
		}
		bzero(buf,MAX_BUF_SIZE);
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
				bzero(buf,MAX_BUF_SIZE);
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
					bzero(buf,MAX_BUF_SIZE);
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
	}
	return 0; 
}

/*----------------------------上传响应------------------------------------------*/
int recv_upload(const int sock_fd,char *buf,const int auth)
{
	if(auth!=-1)
	{
		bzero(buf,MAX_BUF_SIZE);
		if(recv(sock_fd,buf,MAX_BUF_SIZE,0)<0)
		{
			perror("Error: fail to recv!\n");
			return -1;
		}
		int tot=*(int*)buf;
		char tmp[1024];
		char filename[1024]=ADDR_ST;
		bzero(tmp,sizeof(tmp)); 
		bcopy(&buf[4],tmp,strlen(&buf[4]));
		bzero(buf,MAX_BUF_SIZE);
		buf[0]='1';
		if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
		{
			perror("Error: fail to send!\n");
			return -1;
		}
		strcat(filename,tmp);
		FILE *fp=fopen(filename,"wb");
		if(fp==NULL)
		{
			perror("Error: fail to open file!\n");
			return -1;
		}
		while(tot)
		{
			int size=0;
			bzero(buf,MAX_BUF_SIZE);
			if(recv(sock_fd,buf,MAX_BUF_SIZE,0)<0)
			{
				perror("Error: fail to recv!\n");
				return -1;
			}
			if(tot-MAX_BUF_SIZE>=0)
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
				return 1;
			}
			bzero(buf,MAX_BUF_SIZE);
			buf[0]='1';
			if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
			{
				perror("Error: fail to send!\n");
				fclose(fp);
				return -1;
			}
		}
		fclose(fp);
	}
	return 0; 
}

/*----------------------------下载响应------------------------------------------*/
int recv_download(const int sock_fd,char *buf,const int auth)
{
	if(auth!=-1)
	{
		bzero(buf,MAX_BUF_SIZE);
		if(recv(sock_fd,(void*)buf,MAX_BUF_SIZE,0) < 0)
		{	
			perror("Error: fail to recv!\n");
			return -1;
		}
		char tmp[1024];
		char filename[1024]=ADDR_ST;
		int tot;
		bzero(tmp,sizeof(tmp));
		bcopy(tmp,buf,strlen(buf));
		strcat(filename,tmp);
		if((tot=get_file_size(filename))<0)
		{
			perror("Error: fail to get file size!\n");
			return -1;
		}
		bzero(buf,MAX_BUF_SIZE);
		*(int*)buf=tot;
		if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
		{
			perror("Error: fail to send!\n");
			return -1;
		}
		FILE *fp=fopen(filename,"rb");
		if(fp==NULL)
		{
			perror("Error: fail to open file!\n");
			return -1;
		}
		while(tot)
		{
			int size=0;
			bzero(buf,sizeof(buf));
			if(tot-MAX_BUF_SIZE>=0)
			{
				size=MAX_BUF_SIZE;
				tot-=MAX_BUF_SIZE;	
			}	
			else
			{
				size=tot;
				tot=0;
			}
			if(fread(buf,sizeof(char),size,fp)<size);
			{
				perror("Error: fail to read!\n");
				fclose(fp);
				return -1;
			}
			if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
			{
				perror("Error: fail to send!\n");
				fclose(fp);
				return -1;
			}
			bzero(buf,MAX_BUF_SIZE);
			if(recv(sock_fd,(void*)buf,MAX_BUF_SIZE,0) < 0)
			{	
				perror("Error: fail to recv!\n");
				fclose(fp);
				return -1;
			}
			if(buf[1]!='1')	break;
		}
		fclose(fp);
	}
	return 0;
}

/*----------------------------删除响应------------------------------------------*/
int recv_del(const int sock_fd,char *buf,const int auth)
{
	if(auth==1)
	{
		bzero(buf,MAX_BUF_SIZE);
		if(recv(sock_fd,(void*)buf,MAX_BUF_SIZE,0) < 0)
		{	
			perror("Error: fail to recv!\n");
			return -1;
		}
		char tmp[1024];
		char filename[1024]=ADDR_ST;
		bzero(tmp,sizeof(tmp));
		bcopy(tmp,buf,strlen(buf));
		strcat(filename,tmp);
		if(remove(filename)<0)
		{
			perror("Error: fail to remove file!\n");
			return 1;
		}
		else
			return 0;
	}
	return INFINITE;
}

/*----------------------------修改响应------------------------------------------*/
int recv_modify(const int sock_fd,char *buf,const int auth)
{
	if(auth==1)
	{
		bzero(buf,MAX_BUF_SIZE);
		if(recv(sock_fd,(void*)buf,MAX_BUF_SIZE,0) < 0)
		{	
			perror("Error: fail to recv!\n");
			return -1;
		}
		char tmp[1024];
		char oldfilename[1024]=ADDR_ST;
		bzero(tmp,sizeof(tmp));
		bcopy(tmp,buf,strlen(buf));
		strcat(oldfilename,tmp);
		bzero(buf,MAX_BUF_SIZE);
		buf[0]='1';
		if(send(sock_fd,buf,MAX_BUF_SIZE,0)<0)
		{
			perror("Error: fail to send!\n");
			return -1;
		}
		bzero(buf,MAX_BUF_SIZE);
		if(recv(sock_fd,(void*)buf,MAX_BUF_SIZE,0) < 0)
		{	
			perror("Error: fail to recv!\n");
			return -1;
		}
		char newfilename[1024]=ADDR_ST;
		bzero(tmp,sizeof(tmp));
		bcopy(tmp,buf,strlen(buf));
		strcat(newfilename,tmp);
		if(rename(oldfilename,newfilename)<0)
		{
			perror("Error: fail to modify file name!\n");
			return 1;
		}
		else
			return 0;
	}
	return INFINITE;
}

/*----------------------------底层函数------------------------------------------*/
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
