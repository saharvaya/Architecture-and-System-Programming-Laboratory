# All Targets
all: myshell

# Tool invocations
myshell: task1.o LineParser.o
	gcc -g -m32  task1.o LineParser.o -o myshell


# Depends on the source and header files
task1.o: task1.c
	gcc -g -m32 -Wall -ansi -c  task1.c -o task1.o

# Depends on the source and header files
LineParser.o: LineParser.c
	gcc -g -m32 -Wall -ansi -c  LineParser.c -o LineParser.o

.PHONY: clean
	
#Clean the build directory
clean: 
	rm -f *.o myshell

