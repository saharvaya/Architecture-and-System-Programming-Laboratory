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
    char* input=(char*)malloc(100);
    printf("%s\n","Please enter file name");
    input=fgets(input,100,stdin);
	sscanf(input,"%s",s->file_name);
	if(s->debug_mode=='1')
        printf("Debug: file name set to '%s'\n",s->file_name);
    
}

void setusize(state *s){
    char* input=(char*)malloc(100);
    int unitsize;
    printf("%s\n","Please enter unit size");
    input=fgets(input,100,stdin);
	unitsize=atoi(input);
    if(unitsize!=1 && unitsize!=2&&unitsize!=4)
        printf("not valid unit size");
    else{
        s->unit_size=unitsize;
        if(s->debug_mode=='1')
            printf("Debug: set size to %d\n",unitsize);
    }
    free(input);
        
}

void memoryload(state* s){
    FILE* fp;
    char* input=(char*)malloc(100);
    int length;
    char* location=(char*)malloc(100);
    long int locationvalue;
    if(s->file_name[0]==0){
        printf("file name error");
        free(input);
        return;
    }
    
    fp=fopen(s->file_name,"r");
    if(!fp){
        printf("error in open file");
        free(input);
        return;
    }
    else{
        printf("Please enter <location> <length>");
        fgets(input,100,stdin);
        sscanf(input,"%s",location);
        input=input+strlen(location);
        length=atoi(input);
        input=input-strlen(location);
        locationvalue=strtol(location,NULL,16);
        if(s->debug_mode=='1'){
                printf("file name: %s\n",s->file_name);
                printf("location: %ld\n",locationvalue);   
                printf("length: %d\n",length);
        }
        fseek(fp,locationvalue,SEEK_SET);
        int success=fread(s->mem_buf,s->unit_size,length,fp);
        if(success>0){
            printf("Loaded %d units into memory\n",length);
            s->mem_count=s->mem_count+length;
        }
        else
            printf("error while reading bytes from file");
        
        fclose(fp);
        
    }
    free(input);
    free(location);
}

char* unit_to_format(int unit) {
    static char* formats[] = {"%#hhx\n", "%#hx\n", "No such unit", "%#x\n"};
    return formats[unit-1];
}

void memdisp(state* s){
    char* buf=(char*)malloc(10000);
    FILE* fp;
    char* input=(char*)malloc(100);
    int u;
    char* location=(char*)malloc(100);
    long int addressvalue;
    printf("Please enter <address> <length>");
       fgets(input,100,stdin);
        sscanf(input,"%s",location);
        input=input+strlen(location);
        u=atoi(input);
        input=input-strlen(location);
        addressvalue=strtol(location,NULL,16);
        if(s->file_name[0]==0){
            printf("file name error");
            free(input);
            return;
        }
        
    
        fp=fopen(s->file_name,"r");
        if(!fp){
            printf("error in open file");
            free(input);
            return;
        }
        fseek(fp,addressvalue,SEEK_SET);
        int success=fread(buf,s->unit_size,u,fp);
        if(success>0){
        printf("Decimal   Hexadecimal\n");
        printf("=============\n");
        char* end = buf + s->unit_size*u;
        while (buf < end) {
            int var = *((int*)(buf));
            printf("%d   ",var);
            printf(unit_to_format(s->unit_size), var);
            buf =buf+s->unit_size;
            printf("\n");
        }

        }
        else{
            printf("error while reading bytes from file");
        }
        
        fclose(fp);
    free(input);
    free(location);

    
}

 
int main(int argc, char **argv){
  int i,bounds;
  char *choose=(char*)malloc(5);
  state* s=(state*)malloc(sizeof(state));
    struct fun_desc menu[]={{"Toggle Debug Mode",toggle},{"Set File Name",setfname},{"Set Unit Size",setusize},{"Load Into Memory",memoryload},{"Memory Display",memdisp},{"Quit",quit},{"Null",NULL}};
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
    fgets(choose,10,stdin);
    int ch1;
    sscanf(choose,"%d",&ch1);
    if(ch1>=bounds || ch1<0){
        printf("Not within bounds\n");
        free(choose);
        quit(s);
    }
    else{
        printf("Whithin bounds\n");
        menu[ch1].fun(s);
    
        }
    }
    
    return 0;
}
