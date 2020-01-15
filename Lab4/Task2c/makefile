
# All Targets
all: task1

# Tool invocations
task1: main.o start.o util.o
	ld -m elf_i386  start.o main.o util.o -o task1

# Depends on the source and header files
main.o: main.c
	gcc -g -m32 -Wall -ansi -c -nostdlib -fno-stack-protector main.c -o main.o

# Depends on the source and header files
util.o: util.c
	gcc -g -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o
	
# Depends on the source and header files
start.o: start.s
	nasm -f elf -g start.s -o start.o

.PHONY: clean
	
#Clean the build directory
clean: 
	rm -f *.o task1
