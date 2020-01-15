# All Targets
all: hexeditplus

# Tool invocations
hexeditplus: hexeditplus.o
	gcc -g -m32  hexeditplus.o -o hexeditplus


# Depends on the source and header files
hexeditplus.o: hexeditplus.c
	gcc -g -m32 -Wall -ansi -c  hexeditplus.c -o hexeditplus.o

.PHONY: clean
	
#Clean the build directory
clean: 
	rm -f *.o hexeditplus

