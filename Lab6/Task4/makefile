# All Targets
all: myshell

# Tool invocations
myshell: task4.o LineParser.o
	gcc -g -m32  task4.o LineParser.o -o myshell


# Depends on the source and header files
task4.o: task4.c
	gcc -g -m32 -Wall -ansi -c  task4.c -o task4.o

# Depends on the source and header files
LineParser.o: LineParser.c
	gcc -g -m32 -Wall -ansi -c  LineParser.c -o LineParser.o

.PHONY: clean
	
#Clean the build directory
clean: 
	rm -f *.o myshell

