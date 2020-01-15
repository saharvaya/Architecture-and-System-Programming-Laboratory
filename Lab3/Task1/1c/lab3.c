#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSZ 16

typedef struct virus {
    unsigned short SigSize;
    char virusName[16];
    char sig[];
} virus;

typedef struct link link;
 
struct link {
    link *nextVirus;
    virus *vir;
};

char* detectBuffer;
link *viruses=NULL;


link* list_append(link* virus_list,virus* data){
	link *temp = virus_list;

	if(virus_list == NULL) {

		virus_list = (link*)malloc(sizeof(struct link));

		virus_list->vir = data;

		virus_list->nextVirus = NULL;

		return virus_list;

	}

	

	while(temp->nextVirus != NULL)

		temp = temp->nextVirus;

	temp->nextVirus = (link*)malloc(sizeof(link));

	temp->nextVirus->vir = data;

	temp->nextVirus->nextVirus = NULL;



	return virus_list;
    
}

void list_free(link *virus_list){
    link *temp;
    
    while(virus_list!=NULL){
     free(virus_list->vir);
     temp=virus_list;
     virus_list=virus_list->nextVirus;
     free(temp);
    }
}
int PrintHex(char buffer[],int length){
    int i;
    printf("signature: ");
    printf("\n");
    for(i=0;i<length;i++){
        printf(" %02X ",(unsigned char)buffer[i]);
    }
    printf("\n");
    printf("\n");
    return 0;
}



void list_print(link *virus_list){
    while(virus_list!=NULL){
        printf("Virus name: %s\n", virus_list->vir->virusName);

        printf("Virus size: %d\n", virus_list->vir->SigSize-18);
        PrintHex(virus_list->vir->sig,virus_list->vir->SigSize-18);
        virus_list=virus_list->nextVirus;
        
    }
}

void detect_virus(char *buffer, unsigned int size){
    link *temp=viruses;
    int i;
    short sigsize;
    char * sigtemp;
    while(temp!=NULL){
        sigtemp=temp->vir->sig;
        sigsize=temp->vir->SigSize-18;
        for(i=0;i<size;i++){
            if(memcmp(buffer+i,sigtemp,sigsize)==0){
                printf("The starting byte location in the suspected file: %d\n",i);
                printf("The virus name: %s\n",temp->vir->virusName);
                printf("The size of the virus signature: %d\n",temp->vir->SigSize-18);
            }
        }
        printf("\n");
        temp=temp->nextVirus;
    }
    
}



int main(int argc, char **argv){
    unsigned short length;
    char *filename=(char*)malloc(20);
    int i,size,viruslocation,virusize;
    char* choose=(char*)malloc(20);
    FILE* in=stdin;
    FILE* fp;
    FILE* detector;
    detectBuffer=(char*)calloc(10000,sizeof(char));
     char *menu[]={"Load signatures","Print signatures","Detect viruses","Quit"};
    
    while(1){
        for(i=1;i<5;i++){
        printf("%d) %s\n",i,menu[i-1]);
        }
    choose=fgets(choose,10,in);
    
    switch(atoi(choose)){
        case 1:
            filename=fgets(filename,20,stdin);
            sscanf(filename, "%s", filename);
            if(viruses==NULL)
                list_free(viruses);
            fp = fopen(filename, "rb" );
                if (!fp) {
                    fprintf (stderr, "error: file open failed '%s'.\n", argv[1]);
                    return 1;
                }
                
            while(fread (&length,2,1,fp)!=0){
                struct virus *virus=(struct virus*)malloc(length);
                virus->SigSize=length;
                fread(virus->virusName,BUFSZ,1,fp);
                fread(&(virus->sig),length-18,1,fp);
                viruses=list_append(viruses,virus);
            }
        fclose(fp);
        break;
        
        case 2:
            list_print(viruses);
            break;
        
        case 3:
            filename=fgets(filename,20,stdin);
            sscanf(filename, "%s", filename);
            detector=fopen(filename,"rb");
            if (!detector) {
                fprintf (stderr, "error: file open failed '%s'.\n", argv[1]);
                }
            else{
                fseek(detector, 0, SEEK_END);
                size = ftell(detector);
                fseek(detector, 0, SEEK_SET);
                fread(detectBuffer,size,1,detector);
                fclose(detector);
                detect_virus(detectBuffer,size); 
            }
            
            break;
            
            
        case 4:
            list_free(viruses);
            free(filename);
            free(choose);
            free(detectBuffer);
            exit(0);
            
    }
    
   }
  

}
