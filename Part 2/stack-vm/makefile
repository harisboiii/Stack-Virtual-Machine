# Set the C++11 flag
CFLAGS=-std=c++11

# Default target is to build the stack-vm executable
all: stack-vm

# Build the stack-vm executable by linking stack-vm.o and main.o
stack-vm: stack-vm.o main.o
	$(CXX) $(CFLAGS) stack-vm.o main.o -o stack-vm

# Compile main.cpp to produce main.o
main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

# Compile stack-vm.cpp to produce stack-vm.o
stack-vm.o: stack-vm.h stack-vm.cpp
	$(CXX) $(CFLAGS) -c stack-vm.cpp

# Remove object files and the stack-vm executable
clean:
	rm -f *.o stack-vm
