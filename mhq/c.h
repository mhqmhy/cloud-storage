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
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*-----------------------Macros----------------------------------*/

#define N 4096
#define MAX_BUF_SIZE 4096
typedef struct sockaddr AS;
#define ADDR_ST "./bdCloud_Download/"

/*---------------------Functions--------------------------------*/

unsigned long get_file_size(char *path);

char *get_file_name(char *name);

struct sockaddr_in taojiekou();

int ProcessList(vector<string> &myList,string userName, string loginPassword);

int ProcessPut( char pathname[],string userName,string loginPassword);//上传文件

int ProcessGet(char pathname[],string userName,string loginPassword);//2下载文件

int ProcessDelete(string command,string userName, string loginPassword);

int ProcessRename(string command,string userName,string loginPassword);

void PrintHelp();

/*--------------------MY_LIB----------------------------------*/

#include "c.cpp"