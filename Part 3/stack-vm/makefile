CFLAGS=-std=c++11 # Set the CFLAGS variable to specify that the C++11 standard should be used when compiling

all: stack-vm # The default target is 'all', which depends on the 'stack-vm' target

stack-vm: stack-vm.o main.o # The 'stack-vm' target depends on the 'stack-vm.o' and 'main.o' object files
	$(CXX) $(CFLAGS) stack-vm.o main.o -o stack-vm # Link the object files together to create the 'stack-vm' executable

main.o: main.cpp # The 'main.o' target depends on the 'main.cpp' source file
	$(CXX) $(CFLAGS) -c main.cpp # Compile the 'main.cpp' source file into the 'main.o' object file

stack-vm.o: stack-vm.h stack-vm.cpp # The 'stack-vm.o' target depends on the 'stack-vm.h' header file and the 'stack-vm.cpp' source file
	$(CXX) $(CFLAGS) -c stack-vm.cpp # Compile the 'stack-vm.cpp' source file into the 'stack-vm.o' object file

clean: # The 'clean' target has no dependencies
	rm -f *.o stack-vm # Remove all object files and the 'stack-vm' executable
