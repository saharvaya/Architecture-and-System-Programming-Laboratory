#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char** argv){
    char c,enc[]="";
    
    FILE *in=stdin,*out=stdout;
    int DebugFlag=0,encFlag1=0,encFlag2=0,i,j=0;
    
    for(i=1;i<argc;i++){
        if(strcmp(argv[i],"-D")==0){
            DebugFlag=1;
            fprintf(stderr,"%s\n",argv[i]);
        }
        else if(strncmp(argv[i],"+e",2)==0){
            encFlag1=1;
            strcpy(enc,argv[i]+2);
        }
        else if(strncmp(argv[i],"-e",2)==0){
            encFlag2=1;
            strcpy(enc,argv[i]+2);
        }
        else if(strncmp(argv[i],"-i",2)==0){
            in=fopen(argv[i]+2,"r");
        }
        else if(strncmp(argv[i],"-o",2)==0){
            out=fopen(argv[i]+2,"w");
        }
        else{
            printf("invalid parameter - %s\n",argv[i]);
            return 1;
    }
        
    }

    c=fgetc(in);
    while(c!=EOF){
        
        if(DebugFlag==1)
            fprintf(stderr,"0x%02x\t",(int)c);
        if(encFlag1==1)
            c=c+enc[j];
        
        
        if(encFlag2==1)
            c=c-enc[j];
     
        else if(c<='Z' && c>='A')
            c=c+32;
        
        if(DebugFlag==1)
            fprintf(stderr,"0x%02x\n",(int)c);
        
        fputc(c,out);
           
        if((encFlag1==1||encFlag2==1) &&j==strlen(enc)-1)
            j=0;
        else
            j=j+1;
        
        c=fgetc(in);
    }
    
    fclose(in);
    fclose(out);
    
    return 0;
}
