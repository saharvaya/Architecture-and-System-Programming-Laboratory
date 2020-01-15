#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char** argv){
char c;
FILE *in=stdin,*out=stdout;

c=fgetc(in);
while(c!=EOF){
    if(c<='Z' && c>='A')
        c=c+32;
    fputc(c,out);
    c=fgetc(in);
}

fclose(in);
fclose(out);

return 0;
}
