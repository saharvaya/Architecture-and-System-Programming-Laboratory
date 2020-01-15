#include <stdlib.h>
#include<stdio.h>
#include <string.h>

int main(int argc, char **argv){
    int iarray[] = {1,2,3};
    char carray[] = {'a','b','c'};
    int* iarrayPtr;
    char* carrayPtr;
    int i;
    char* p;

    iarrayPtr=&iarray[0];
    carrayPtr=&carray[0];
    
    for(i=0;i<3;i++){
     printf("%i, ",*(iarrayPtr+i));   
    }
    
    printf("\n");   

    for(i=0;i<3;i++){
     printf("%c, ",*(carrayPtr+i));   
    }
    
    printf("\n"); 
    
    printf("%s",p);

    
}
