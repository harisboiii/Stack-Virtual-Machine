# Compiler flags
CFLAGS=-std=c++11

# Default target
all: stack-vm

# Linking target
stack-vm: stack-vm.o main.o
	$(CXX) $(CFLAGS) stack-vm.o main.o -o stack-vm

# Compile main.cpp
main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

# Compile stack-vm.cpp
stack-vm.o: stack-vm.h stack-vm.cpp
	$(CXX) $(CFLAGS) -c stack-vm.cpp

# Clean target
clean:
	rm -f *.o stack-vm
