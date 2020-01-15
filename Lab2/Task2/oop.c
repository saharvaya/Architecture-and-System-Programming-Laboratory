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
 
int main(int argc, char **argv){
  /* TODO: Test your code */
    int base_len = 5;
    char arr1[base_len];
    char* arr2 = map(arr1, base_len, my_get);
    char* arr3 = map(arr2, base_len, encrypt);
    char* arr4 = map(arr3, base_len, xprt);
    char* arr5 = map(arr4, base_len, decrypt);
    char* arr6 = map(arr5, base_len, cprt);
    free(arr2);
    free(arr3);
    free(arr4);
    free(arr5);
    free(arr6);
}
