# All Targets
all: myecho

# Tool invocations
myecho: my_echo.o 
	gcc -m32 -g -Wall -o myecho my_echo.o 

# Depends on the source and header files
my_echo.o: my_echo.c 
	gcc -g -Wall -m32  -c -o my_echo.o my_echo.c 

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o myecho
