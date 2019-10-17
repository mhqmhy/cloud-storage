/*------------------------LIBS-------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <dirent.h>

/*-----------------------Macros----------------------------------*/

#define PORT 8000
#define MAX_BUF_SIZE 4096
#define MAX_CONNECT 20
#define ADMIN_PSD "981122"
#define USER_PSD "123456"
#define PSD_LEN 6
#define ADDR_ST "../bdCloud_STORE/"
#define INFINITE 0x3f3f3f3f

/*---------------------Functions--------------------------------*/

int recv_header(const int sock_fd,char *buf,int *auth);

int recv_dir(const int sock_fd,char *buf,const int auth);

int recv_upload(const int sock_fd,char *buf,const int auth);

int recv_download(const int sock_fd,char *buf,const int auth);

int recv_del(const int sock_fd,char *buf,const int auth);

int recv_modify(const int sock_fd,char *buf,const int auth);

unsigned long get_file_size(const char *path);

/*--------------------MY_LIB----------------------------------*/
#include "bdCloud_Lib.c"
