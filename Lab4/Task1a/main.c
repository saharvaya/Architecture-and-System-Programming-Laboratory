#include "util.h"

#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_LSEEK 19
#define STDIN 0
#define STDOUT 1
#define STDERR 2

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

int main (int argc , char* argv[], char* envp[])
{
  int i,DebugFlag=0,returntype;
  char buffer[1000];
  
  for(i=1;i<argc;i++){
      if(strcmp("-D",argv[i])==0){
          DebugFlag=1;
          system_call(SYS_WRITE,STDERR,argv[i],strlen(argv[i]));
          system_call(SYS_WRITE,STDERR,"\n",strlen("\n"));
      }
  }

    returntype=system_call(SYS_READ,STDIN,buffer,1000);
    debugger(DebugFlag,(char)SYS_READ,returntype);
    i=0;
    while(buffer[i]!=0){
         if((buffer[i]>='A'&&buffer[i]<='Z'))
            buffer[i]=buffer[i]+32;
        i++;
    }
   returntype=system_call(SYS_WRITE,STDOUT, buffer,strlen(buffer));
    debugger(DebugFlag,(char)SYS_WRITE,returntype);

  return 0;
}
