# All Targets
all: lab3

# Tool invocations
# Executable "encoder" depends on the files encoder.o
lab3: lab3.o
	gcc -g -m32 -Wall -o lab3 lab3.o 

# Depends on the source and header files
lab3.o: lab3.c 
	gcc -m32 -g -Wall -c -o lab3.o lab3.c 
 
#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o lab3
