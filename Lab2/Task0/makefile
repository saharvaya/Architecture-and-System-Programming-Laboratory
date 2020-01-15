# All Targets
all: count

# Tool invocations
# Executable "encoder" depends on the files encoder.o
count: count.o
	gcc -g -m32 -Wall -o lab2 count.o 

# Depends on the source and header files
count.o: count-words.c 
	gcc -m32 -g -Wall -c -o count.o count-words.c 
 
#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o lab2
