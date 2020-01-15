#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include "LineParser.h"

#define PATH_MAX 4096
typedef struct LinkedList {
    char* value;
    char* name;
    struct LinkedList * next;
} LinkedList;

LinkedList* List;

char * findVar(LinkedList* list,char* name){
    LinkedList *iterator = list;
    while(iterator->next != NULL){
        if(strcmp(iterator->name,name) == 0){
            return iterator->value;
        }
        iterator = iterator->next;
    }
    if(strcmp(iterator->name,name) == 0){
        return iterator->value;
    }
    else{
        return "";
    }
}
void list_print(LinkedList *list){
        if(list==NULL)
            return;
        else{
            if(strcmp(list->name,"")==0){
                list_print(list->next);
                return;
            }
        printf("Var name: %s\n", list->name);
        printf("Var value: %s\n", list->value);
        }
        list_print(list->next);
}

void SetVar(LinkedList *list,char * name, char * value){
    LinkedList *iterator = list;
    while(iterator->next != NULL){
        if(strcmp(iterator->name,name) == 0){
            iterator->value = value;
        }
        iterator = iterator->next;
    }
    if(strcmp(iterator->name,name) == 0)
        iterator->value = value;
    else{
        iterator->next = (LinkedList*)malloc(sizeof(LinkedList));
        iterator = iterator->next;
        iterator->name = name;
        iterator->value = value;
        iterator->next = NULL;
    }
}

void DeleteVar(LinkedList* list,char* name){
    LinkedList *iterator = list;
    LinkedList *prev = list;
    int i=0;
    while(iterator->next != NULL){
        if(strcmp(iterator->name,name) == 0){
            prev->next = iterator->next;
            if(i==0)
                List=prev->next;
            free(iterator);
            return;
        }
        i++;
        prev = iterator;
        iterator = iterator->next;
    }
    if(strcmp(iterator->name,name) == 0){
        prev->next = iterator->next;
        free(iterator->value);
        free(iterator->name);
        free(iterator);
    
    }
    else{
        fprintf(stderr, "%s", "var not found !");
    }
}


 char *strClone(char *source)
{
    char* clone = (char*)malloc(strlen(source) + 1);
    strcpy(clone, source);
    return clone;
}


void execute(cmdLine *pCmdLine){
    int PIDex;
    int fd[2];
    int status;
    
    if(pCmdLine->next!=NULL){
        pipe(fd);
        PIDex=fork();
        if(PIDex==0){
            close(1);
            dup(fd[1]);
            close(fd[1]);
        execvp(pCmdLine->arguments[0], pCmdLine->arguments);
        }
        else{
            waitpid(PIDex,&status,0);
            close(fd[1]);
            close(0);
            dup(fd[0]);
            close(fd[0]);
            execvp(pCmdLine->next->arguments[0], pCmdLine->next->arguments);
        }
        close(fd[0]);
    }
    
    if(pCmdLine->inputRedirect!=NULL){
        close(0);
        fopen(pCmdLine->inputRedirect,"r");
    }
    
    if(pCmdLine->outputRedirect!=NULL){
        close(1);
        fopen(pCmdLine->outputRedirect,"w+");
    }
    
    
     if((strcmp(pCmdLine->arguments[0],"cd")==0) ||(strcmp(pCmdLine->arguments[0],"set")==0)|| (strcmp(pCmdLine->arguments[0],"vars")==0) ||(strcmp(pCmdLine->arguments[0],"delete")==0) )
        return;
    
    
    if (execvp(pCmdLine->arguments[0], pCmdLine->arguments) == -1){
        perror("error in execute: ");
        _exit(1);
    }
}

void list_free(LinkedList *list){
    LinkedList *temp;
    
    while(list!=NULL){
    if(strcmp(list->name,"")==0){
        temp=list;
        list=list->next;
        free(temp);
    }
    else{
     free(list->name);
     free(list->value);
     temp=list;
     list=list->next;
     free(temp);
    }
    }
}


int main (int argc , char* argv[], char* envp[])
{
    List=(LinkedList *)malloc(sizeof(LinkedList));
    List->name = "";
    List->value = "";
    List->next = NULL;
    char buffer[PATH_MAX];
    FILE *in=stdin;
    char* input=(char*)malloc(2048);
    cmdLine* cmdl;
    int debugFlag=0,i,status,j;
    pid_t PID;
    char* Varname;
    char* VarVal;
    char* allwords;
    char* FindedVar;
    const char *homedir;
     for(i=1;i<argc;i++){
        if(strcmp("-D",argv[i])==0)
            debugFlag=1;
     }
    
    while(1){
        getcwd(buffer,PATH_MAX);
        printf("%s > ",buffer);
        fgets(input,2048,in);
        allwords=input;
        if(strncmp(input,"set",3)==0){
            strsep(&allwords," ");
            Varname=allwords;
            strsep(&allwords," ");
            VarVal=allwords;
            VarVal[strcspn(VarVal, "\n")] = 0;
            SetVar(List,strClone(Varname),strClone(VarVal));
            
        }
        if(strncmp(input,"vars",4)==0){
            list_print(List);
        }
        if(strncmp(input,"delete",6)==0){
            strsep(&allwords," ");
            Varname=allwords;
            Varname[strcspn(Varname, "\n")] = 0;
            DeleteVar(List,Varname);
        }
        if(strcmp(input,"quit\n")==0){
            list_free(List);
            free(input);
            exit(0);
        }
        else{
            PID=fork();
            cmdl=parseCmdLines(input);
            for(j=0;j<cmdl->argCount;j++){
                if(strncmp(cmdl->arguments[j],"$",1)==0){
                    FindedVar=findVar(List,cmdl->arguments[j]+1);
                    if(strcmp(FindedVar,"")==0)
                        fprintf(stderr, "%s", "Var not found !");
                    else
                        replaceCmdArg(cmdl,j,FindedVar);
                }
            }
            if(strcmp(cmdl->arguments[0],"cd")==0 && strncmp(cmdl->arguments[1],"~",1)==0){
                    struct passwd *pw = getpwuid(getuid());
                    homedir = pw->pw_dir;
                    replaceCmdArg(cmdl,1,homedir);
            }
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
        
        list_free(List);
    }

