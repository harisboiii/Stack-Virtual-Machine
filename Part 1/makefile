# Set the CFLAGS variable to use the C++11 standard
CFLAGS=-std=c++11

# The default target is "all", which depends on the "stack-vm" target
all: stack-vm

# The "stack-vm" target depends on the "stack-vm.o" and "main.o" targets
stack-vm: stack-vm.o main.o
	$(CXX) $(CFLAGS) stack-vm.o main.o -o stack-vm

# The "main.o" target compiles "main.cpp" into an object file
main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

# The "stack-vm.o" target compiles "stack-vm.cpp" into an object file
# It depends on "stack-vm.h" because that file is included by "stack-vm.cpp"
stack-vm.o: stack-vm.h stack-vm.cpp
	$(CXX) $(CFLAGS) -c stack-vm.cpp

# The "clean" target removes all object files and the "stack-vm" executable
clean:
	rm -f *.o stack-vm
