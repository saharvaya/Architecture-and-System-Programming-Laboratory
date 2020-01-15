# All Targets
all: lab2

# Tool invocations
# Executable "encoder" depends on the files encoder.o
lab2: oop.o
	gcc -g -m32 -Wall -o lab2 oop.o 

# Depends on the source and header files
oop.o: oop.c 
	gcc -m32 -g -Wall -c -o oop.o oop.c 
 
#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o lab2
