#include "c.h"
int main(int argc,char *argv[])
{
    vector<string> fileList;
   
    char comm[32];
    PrintHelp();
    char pathname[] ="/home/mhq/shiyan6/lab1.c";
    cout<<get_file_size(pathname)<<endl;

    char tmp[1024] = "lab1.c";
    while(1)
    {
        printf(">> ");
        fgets(comm,32,stdin);
        comm[strlen(comm)-1] = '\0'; 
        switch (comm[0])
        {
        case '0':
        
            ProcessList(fileList,"A","981122");
            break;
        case '1':
            
            ProcessPut(pathname,"A","981122");
            break;
        case '2':
        
            ProcessGet(tmp,"A","981122");
            break;
        case '3':
        
            ProcessDelete("1.pdf","A","981122");
            break;
        case '4':
        
            ProcessRename("1.pdf","A","981122");
            break;
        
        default:
        
            printf("warning! Input again.\n");
            break;
        }   
        if(comm[0] = 'q')
            break;  
   }
    return 0;
}
