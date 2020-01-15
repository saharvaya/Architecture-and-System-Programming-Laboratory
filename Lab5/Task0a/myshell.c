#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "LineParser.h"

#define PATH_MAX 4096

void execute(cmdLine *pCmdLine){
    if (execvp(pCmdLine->arguments[0], pCmdLine->arguments) == -1){
        perror("error:error in execute ");
        _exit(1);
    }
}

int main (int argc , char* argv[], char* envp[])
{
    char buffer[PATH_MAX];
    FILE *in=stdin;
    char* input=(char*)malloc(2048);
    cmdLine* cmdl;
    int debugFlag=0,i,status;
    pid_t PID;
     for(i=1;i<argc;i++){
        if(strcmp("-D",argv[i])==0)
            debugFlag=1;
     }
    
    while(1){
        getcwd(buffer,PATH_MAX);
        printf("%s",buffer);
        fgets(input,2048,in);
        if(strcmp(input,"quit\n")==0)
            exit(0);
        else{
            PID=fork();
            cmdl=parseCmdLines(input);
            if(PID==0){
                execute(cmdl);
                freeCmdLines(cmdl);
                _exit(0);
            }
            else if (strncmp(cmdl->arguments[0], "cd", 2) == 0) {
                if (chdir(cmdl->arguments[1]) == -1) {
                    perror("directory is not exist: ");
                }
            }
            if(debugFlag==1){
                fprintf(stderr,"The PID Is : %d\n",PID);
                fprintf(stderr,"The execute command Is : %s\n",input);
            }
            if(cmdl->blocking == 1){
                waitpid(PID, &status, 0);
            }
        freeCmdLines(cmdl);

            }
        
        }

    }


