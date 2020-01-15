# All Targets
all: myshell

# Tool invocations
myshell: myshell.o LineParser.o
	gcc -g -m32  myshell.o LineParser.o -o myshell


# Depends on the source and header files
myshell.o: myshell.c
	gcc -g -m32 -Wall -ansi -c  myshell.c -o myshell.o

# Depends on the source and header files
LineParser.o: LineParser.c
	gcc -g -m32 -Wall -ansi -c  LineParser.c -o LineParser.o

.PHONY: clean
	
#Clean the build directory
clean: 
	rm -f *.o myshell
