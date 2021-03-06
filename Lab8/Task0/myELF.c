#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define KB(i) ((i)*1<<10)
#define INT sizeof(int)
#define SHORT sizeof(short)
#define BYTE sizeof(char)

#define MAX_FILE_SIZE KB(10)

typedef char bool;
#define true 1
#define false 0

#define O_RDONLY         00
#define O_WRONLY         01
#define O_RDWR           02

struct fun_desc{
 char *name;
 void (*fun)(void);
};


int print_menu();
void quit();
void toggle();
void Examine_ELF();
char* unit_to_format(int unit);

int unit_sizes[] = { BYTE, SHORT, INT,  };

struct fun_desc menu[]={{"Toggle Debug Mode",&toggle}, {"Examine ELF File", &Examine_ELF},{"Print Section Names",&print_sections}, {"Quit", &quit}, {NULL,NULL}};

int Currentfd=-1;
void *map_start; /* will point to the start of the memory mapped file */
struct stat fd_stat; /* this is needed to  the size of the file */
Elf32_Ehdr *header; /* this will point to the header structure */
int num_of_section_headers;
int debug_mode=false;
char file_name[100];

int main(int argc, char **argv)
{
   int option;
   size_t bounds = sizeof(menu)/sizeof(struct fun_desc)-1;
    while(true)
    {
       option = print_menu();
       if(option >= bounds || option < 0){
           printf("Not within bounds\n");
       }
       else
       {
           printf("Within bounds.\n");
           (menu[option].fun)();
       }
    }

    return 0;
}


int print_menu()
{
   int i = 0, choice;
   char * in = (char *)malloc(5);
   printf("\nChoose action:\n");
   while(menu[i].name != NULL)
   {
       printf("%d- %s\n", i, menu[i].name);
       ++i;
   }
   printf("Option: ");
   fgets(in, 10, stdin);
   sscanf(in,"%d", &choice);
   free(in);
   return choice;
}

void quit()
{
    if(debug_mode == true)
        printf("quitting\n");
    exit(0);
}

void toggle()
{
   printf(debug_mode == true ? "Debug flag now off\n" : "Debug flag now on\n");
   debug_mode = debug_mode == true ? false : true;
}

void Examine_ELF(){
   char* input = (char*)malloc(100);
   printf("Please enter file name: ");
   input = fgets(input, 100, stdin);
   sscanf(input,"%s", file_name);
    if(Currentfd!=-1){
        munmap(map_start,fd_stat.st_size);
        close(Currentfd);
    }
    if((Currentfd = open(file_name, O_RDWR)) < 0 ) {
      perror("error in open");
      exit(-1);
   }

   if( fstat(Currentfd, &fd_stat) != 0 ) {
      perror("stat failed");
      exit(-1);
   }

   if ( (map_start = mmap(0, fd_stat.st_size, PROT_READ | PROT_WRITE , MAP_SHARED, Currentfd, 0)) == MAP_FAILED ) {
      perror("mmap failed");
      exit(-4);
   }

   header = (Elf32_Ehdr *) map_start;
   
   printf("%s","The Magic numbers(in ASCII) : ");
   printf("%d",header->e_ident[1]);
   printf("%d",header->e_ident[2]);
   printf("%d\n",header->e_ident[3]);
   
   if((int)(header->e_ident[0])==127 && (header->e_ident[1])=='E' && (header->e_ident[2])=='L'&& (header->e_ident[3])=='F'){
       if(header->e_ident[EI_DATA]==ELFDATANONE)
           printf("invalid data encoding\n");
       if(header->e_ident[EI_DATA]==ELFDATA2LSB)
           printf("data encoding: 2's complement, little endian\n");
       if(header->e_ident[EI_DATA]==ELFDATANONE)
           printf("data encoding: 2's complement, big endian\n");
       printf("Entry point : %x\n",header->e_entry);
       printf("Section header string table index: %d\n", header->e_shoff);
       printf("Number of section headers: %d\n", header->e_shnum);
       printf("Size of section headers: %d\n", header->e_shentsize);
       printf("Start of program headers: %d\n", header->e_phoff);
       printf("The number of program header entries: %d\n", header->e_phnum);
       printf("The size of each program header entry: %d\n", header->e_phentsize);
       
   }
   
   else{
       fprintf(stderr,"ERROR : not ELF file");
        if(Currentfd!=-1){
            munmap(map_start,fd_stat.st_size);
            close(Currentfd);
            Currentfd=-1;
        }
       
   }
   
   
        
}

void print_sections(){
    Elf32_Shdr* section;
    int i;
    if(Currentfd==-1)
        printf("no file open");
    else{
        section=(Elf32_Shdr*)(map_start+header->e_shoff);
        for(i=0;i<header->e_shnum;i++){
            printf("[%d]  %s  0x%x  %d  %d %s\n",i,section->sh_name,section->sh_addr,section->sh_offset,section->sh_size,section->sh_type);
            section=section+sizeof(Elf32_Shdr);
        }
        }
        
    }
    
