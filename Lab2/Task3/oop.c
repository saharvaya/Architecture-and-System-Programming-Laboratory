#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char encrypt(char c){
    if((int)c>=0x20 && (int)c<=0x7E){
        return c+3;
    }
    else
        return c;
}

char decrypt(char c){
    if((int)c>=0x20 && (int)c<=0x7E){
        return c-3;
    }
    else
        return c;
}

char xprt(char c){
    printf("0x%02x\n", (int)c);
    return c;
}

char cprt(char c){
     if((int)c>=0x20 && (int)c<=0x7E){
         printf("%c\n",c);
     }
     else
         printf("%c\n",'.');
     
     return c;
}

char my_get(char c){
    FILE *in=stdin;
    c=fgetc(in);
    return c;

}

char quit(char c){
    exit(0);
}
 
char censor(char c) {
  if(c == '!')
    return '.';
  else
    return c;
}
 
char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
  int i;
  /* TODO: Complete during task 2.a */
  
  for(i=0;i<array_length*sizeof(char);i++){
      *(mapped_array+i)=(*f)(array[i]);
  }
  return mapped_array;
}

struct fun_desc{
 char *name;
 char (*fun)(char);
};
 
int main(int argc, char **argv){
  /* TODO: Test your code */
  int i,bounds;
  FILE *in=stdin;
  char *choose=(char*)malloc(5);
    char *carray=(char*)(malloc(5));
    struct fun_desc menu[]={{"Censor",censor},{"Encrypt",encrypt},{"Decrypt",decrypt},{"Print hex",xprt},
    {"Print string",cprt},{"Get string",my_get},{"Quit",quit},{"Null",NULL}};
    bounds=sizeof(menu)/sizeof(struct fun_desc)-1;
    
    while(1){
    printf("Please choose a function:\n");
    for(i=0;i<sizeof(menu)/sizeof(struct fun_desc)-1;i++){
        printf("%d) %s\n",i,menu[i].name);
    }
    printf("Option: ");
    choose=fgets(choose,10,in);
    if(atoi(choose)>=bounds || atoi(choose)<0){
        printf("Not within bounds\n");
        free(carray);
        free(choose);
        quit('a');
    }
    else
        printf("Whithin bounds\n");
    
    carray=map(carray,5,menu[atoi(choose)].fun);
    printf("DONE.\n\n");

    
    
    }
    
    return 0;
}
