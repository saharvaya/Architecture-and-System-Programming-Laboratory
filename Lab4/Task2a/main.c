#include "util.h"
#include <dirent.h>

#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDRW 2
#define O_CREATE 64
#define SYS_GETDENTS 141

void debugger(int DebugFlag,int id,int returntype){
    if(DebugFlag==1){
        system_call(SYS_WRITE,STDERR,"Debugger:", 9);
        system_call(SYS_WRITE,STDERR,"\n",strlen("\n"));
        system_call(SYS_WRITE,STDERR,"ID:", 3);
        system_call(SYS_WRITE,STDERR,itoa(id),strlen(itoa(id)));
        system_call(SYS_WRITE,STDERR,"\n",strlen("\n"));
        system_call(SYS_WRITE,STDERR,"Return code:", 12);
      system_call(SYS_WRITE,STDERR,itoa(returntype),strlen(itoa(returntype)));
      system_call(SYS_WRITE,STDERR,"\n",strlen("\n"));
    }
    else
        return;
    
}

typedef struct ent{
    int inode;
    int offset;
    short len;
    char buf[];
}ent;


int main (int argc , char* argv[], char* envp[])
{
    int i,DebugFlag=0,returntype,fd,count;
    char buffer[8192];
    struct ent *d;

    
    for(i=1;i<argc;i++){
        if(strcmp("-D",argv[i])==0){
            DebugFlag=1;
            system_call(SYS_WRITE,STDERR,argv[i],strlen(argv[i]));
            system_call(SYS_WRITE,STDERR,"\n",strlen("\n"));
        }

    }
    
    fd=system_call(SYS_OPEN,".",O_RDONLY,0);
    debugger(DebugFlag,SYS_OPEN,fd);

    count=system_call(SYS_GETDENTS,fd,buffer,8192);
    debugger(DebugFlag,SYS_GETDENTS,count);

    
    for (i = 0; i < count;) {
                   d = (struct ent*)(buffer + i);
                   system_call(SYS_WRITE,STDERR,"File name:", 10);
                   returntype=system_call(SYS_WRITE,STDOUT,d->buf,strlen(d->buf));
                   system_call(SYS_WRITE,STDERR,"\n",strlen("\n"));
                   debugger(DebugFlag,SYS_WRITE,returntype);
                   if(DebugFlag==1){
                       system_call(SYS_WRITE,STDERR,"length:", 7);
                       returntype=system_call(SYS_WRITE,STDOUT,itoa(d->len),strlen(itoa(d->len)));
                   }
                   system_call(SYS_WRITE,STDERR,"\n",strlen("\n"));
                   i += d->len;
               }


    return 0;
}
