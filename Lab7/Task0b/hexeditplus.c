#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct {
  char debug_mode;
  char file_name[128];
  int unit_size;
  unsigned char mem_buf[10000];
  size_t mem_count;
  /*
   .
   .
   Any additional fields you deem necessary
  */
} state;

struct fun_desc{
 char *name;
 void (*fun)(state*);
};


void quit(state* s){
    if(s->debug_mode=='1')
        printf("quitting\n");
    exit(0);
}

void toggle(state* s){
    if(s->debug_mode=='1'){
        printf("Debug flag now off\n");
        s->debug_mode='0';
    }
    else{
        printf("Debug flag now on\n");
        s->debug_mode='1';
    }
}

void setfname(state *s){
    printf("%s\n","Please enter file name");
	scanf("%100s",s->file_name);
	if(s->debug_mode=='1')
        printf("Debug: file name set to '%s'\n",s->file_name);
}

void setusize(state *s){
    int unitsize;
    printf("%s\n","Please enter unit size");
    scanf("%d",&unitsize);
    if(unitsize!=1 && unitsize!=2&&unitsize!=4)
        printf("not valid unit size");
    else{
        s->unit_size=unitsize;
        if(s->debug_mode=='1')
            printf("Debug: set size to %d\n",unitsize);
    }
        
}

 
int main(int argc, char **argv){
  int i,bounds;
  FILE *in=stdin;
  char *choose=(char*)malloc(5);
  state* s=(state*)malloc(sizeof(state));
    struct fun_desc menu[]={{"Toggle Debug Mode",toggle},{"Set File Name",setfname},{"Set Unit Size",setusize},{"Quit",quit},{"Null",NULL}};
    bounds=sizeof(menu)/sizeof(struct fun_desc)-1;
    
    while(1){
    if(s->debug_mode=='1'){
        printf("Unit size : %d\n",s->unit_size);
        printf("File Name : %s\n",s->file_name);
        printf("Mem count : %zu\n",s->mem_count);
    }
    printf("Choose action:\n");
    for(i=0;i<sizeof(menu)/sizeof(struct fun_desc)-1;i++){
        printf("%d- %s\n",i,menu[i].name);
    }
    printf("Option: ");
    choose=fgets(choose,10,in);
    if(atoi(choose)>=bounds || atoi(choose)<0){
        printf("Not within bounds\n");
        free(choose);
        quit('a');
    }
    else{
        printf("Whithin bounds\n");
        menu[atoi(choose)].fun(s);
    
    }
    }
    
    return 0;
}
