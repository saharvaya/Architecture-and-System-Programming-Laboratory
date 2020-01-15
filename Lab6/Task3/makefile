# All Targets
all: myshell

# Tool invocations
myshell: task3.o LineParser.o
	gcc -g -m32  task3.o LineParser.o -o myshell


# Depends on the source and header files
task3.o: task3.c
	gcc -g -m32 -Wall -ansi -c  task3.c -o task3.o

# Depends on the source and header files
LineParser.o: LineParser.c
	gcc -g -m32 -Wall -ansi -c  LineParser.c -o LineParser.o

.PHONY: clean
	
#Clean the build directory
clean: 
	rm -f *.o myshell

