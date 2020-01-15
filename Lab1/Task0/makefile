
# All Targets
all: task0

# Tool invocations
ass0: main.o numbers.o add.o
	gcc -g -m32 -Wall -o task0 main.o numbers.o add.o

# Depends on the source and header files
main.o: main.c
	gcc g -m32 -Wall -c -o main.o main.c

# Depends on the source and header files
numbers.o: numbers.c
	gcc -g -m32 -Wall -c -o numbers.o numbers.c
	
# Depends on the source and header files
add.o: add.s
	nasm -g -f elf -w+all -o add.o add.s

.PHONY: clean
	
#Clean the build directory
clean: 
	rm -f *.o ass0
