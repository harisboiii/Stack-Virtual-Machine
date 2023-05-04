# Define the compiler flags to use (C++11 standard).
CFLAGS=-std=c++11

# Define the default target (all) and its dependencies (stack-vm).
all: stack-vm

# Define the target for building the executable (stack-vm) and its dependencies (stack-vm.o and main.o).
stack-vm: stack-vm.o main.o
	$(CXX) $(CFLAGS) stack-vm.o main.o -o stack-vm

# Define the target for building the main object file (main.o) and its dependencies (main.cpp).
main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

# Define the target for building the stack-vm object file (stack-vm.o) and its dependencies (stack-vm.h and stack-vm.cpp).
stack-vm.o: stack-vm.h stack-vm.cpp
	$(CXX) $(CFLAGS) -c stack-vm.cpp

# Define the target for cleaning up the project (removing object files and executable).
clean:
	rm -f *.o stack-vm
