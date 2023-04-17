# Compiler flags for using C++11 standard
CFLAGS=-std=c++11

# Default target that will be built when 'make' is run
all: stack-vm

# Target for building the stack-vm executable
stack-vm: stack-vm.o main.o
        $(CXX) $(CFLAGS) stack-vm.o main.o -o stack-vm

# Target for building the main.o object file
main.o: main.cpp
        $(CXX) $(CFLAGS) -c main.cpp

# Target for building the stack-vm.o object file
stack-vm.o: stack-vm.h stack-vm.cpp
        $(CXX) $(CFLAGS) -c stack-vm.cpp

# Target for cleaning up object files and the stack-vm executable
clean: 
        rm -f *.o stack-vm

