#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main (int argc , char* argv[], char* envp[])
{
    int child1PID,child2PID,status,debugFlag=0,i=0;
    int fd[2];
    char* args1[3];
    char* args2[4];
    args1[0]="ls";
    args1[1]="-l";
    args1[2]=NULL;
    args2[0]="tail";
    args2[1]="-n";
    args2[2]="2";
    args2[3]=NULL;
    for(i=1;i<argc;i++){
        if(strcmp("-d",argv[i])==0)
            debugFlag=1;
     }
    pipe(fd);
    if(debugFlag==1)
        fprintf(stderr,"(parent_process>forking…)\n");
    child1PID=fork();
    if(debugFlag==1)
        fprintf(stderr,"(parent_process>created process with id: %d)\n",child1PID);
    
    if(child1PID==0){
        if(debugFlag==1)
            fprintf(stderr,"(child1>redirecting stdout to the write end of the pipe…)\n");
        close(1);
        dup(fd[1]);
        close(fd[1]);
        if(debugFlag==1)
            fprintf(stderr,"(child1>going to execute cmd: …)\n");
        execvp(args1[0],args1);
    }
    
    else{
        if(debugFlag==1)
            fprintf(stderr,"(parent_process>closing the write end of the pipe…)\n");
        close(fd[1]);
        child2PID=fork();
        if(child2PID==0){
            if(debugFlag==1)
                fprintf(stderr,"(child2>redirecting stdin to the write end of the pipe…)\n");
            close(0);
            dup(fd[0]);
            close(fd[0]);
            if(debugFlag==1)
                fprintf(stderr,"(child2>going to execute cmd: …)\n");
            execvp(args2[0],args2);
        }
        else{
            if(debugFlag==1)
                fprintf(stderr,"(parent_process>closing the read end of the pipe…)\n");
            close(fd[0]);
            if(debugFlag==1)
                fprintf(stderr,"(parent_process>waiting for child processes to terminate…)\n");
            waitpid(child1PID,&status,0);
            waitpid(child2PID,&status,0);
            
        }

    }
    if(debugFlag==1)
        fprintf(stderr,"(parent_process>exiting…)\n");
    return 0;
    


}
    
