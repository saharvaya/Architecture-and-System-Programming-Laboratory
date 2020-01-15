#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "LineParser.h"

#define PATH_MAX 4096
#define TERMINATED  -1
#define RUNNING 1
#define SUSPENDED 0


typedef struct process{
    cmdLine* cmd;                         /* the parsed command line*/
    pid_t pid; 		                  /* the process id that is running the command*/
    int status;                           /* status of the process: RUNNING/SUSPENDED/TERMINATED */
    struct process *next;	                  /* next process in chain */
} process;

process* Process_list;
void updateProcessList(process **process_list);
void freeProcessList(process* process_list);

void addProcess(process** process_list, cmdLine* cmd,pid_t pid){
    process* iterator=Process_list;
    if(Process_list==NULL){
      Process_list = (process*)malloc(sizeof(struct process));
      Process_list->cmd=cmd;
      Process_list->pid=pid;
      Process_list->status=1;
      return;
    }
    
    while(iterator->next != NULL)
        iterator = iterator->next;
    
      iterator->next = (process**)malloc(sizeof(struct process));
      iterator->next->cmd=cmd;
      iterator->next->pid=pid;
      iterator->next->status=1;
    return;
    
}

void printProcessList(process** process_list){
    updateProcessList(process_list);
    process* iterator=Process_list;
    process* prev=Process_list;
    process* temp;
    int i=0,j;
     while(iterator!= NULL)
    {
         printf("the index of process is %d  " , i);
         printf("\n");
         printf("the id of process is %d  " , iterator->pid);
         printf("\n");
         printf("the status of process is %d  " , iterator->status);
         printf("\n");
         for(j=0;j<iterator->cmd->argCount;j++){
            printf("the command of process is %s  " , iterator->cmd->arguments[j]);
            printf("\n");
         }
         i++;
         
         if(iterator->status==TERMINATED){
             if(iterator==Process_list)
                 Process_list=Process_list->next;
            prev->next=iterator->next;
            temp=iterator;
            iterator=iterator->next;
             freeProcessList(temp);
         }
         else{
             prev=iterator;
            iterator=prev->next;
        }
    }
     return;
    
}

void freeProcessList(process* process_list){
         free(process_list->cmd);
         free(process_list);
     }


void updateProcessStatus(process* process_list, int pid, int status){
     process* iterator=process_list;
     
     while(iterator!=NULL){
         if(iterator->pid==pid)
             iterator->status=status;
     }
     return;
}

void updateProcessList(process **process_list){
     process* iterator=Process_list;
     int stat,pid;
     while(iterator!=NULL){
         pid=waitpid(iterator->pid,&stat,WNOHANG);
         if(pid==-1){
             iterator->status=TERMINATED;
         }
         iterator=iterator->next;
     }
}
    
    
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
        printf("%s > ",buffer);
        fgets(input,2048,in);
        if(strcmp(input,"quit\n")==0)
            exit(0);
        if(strcmp(input,"procs\n")==0)
            printProcessList(&Process_list);
        else{
            PID=fork();
            cmdl=parseCmdLines(input);
            addProcess(&Process_list,cmdl,PID);
            if(PID==0){
                execute(cmdl);
                _exit(0);
            }
             if (strncmp(cmdl->arguments[0], "cd", 2) == 0) {
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

            }
        
        }

    }

