# All Targets
all: myshell

# Tool invocations
myshell: mypipeline.o
	gcc -g -m32  mypipeline.o -o myshell


# Depends on the source and header files
mypipeline.o: mypipeline.c
	gcc -g -m32 -Wall -ansi -c  mypipeline.c -o mypipeline.o

.PHONY: clean
	
#Clean the build directory
clean: 
	rm -f *.o myshell

