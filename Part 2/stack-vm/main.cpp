// Include the header file for the stack-based virtual machine
#include "stack-vm.h"

// Main function
int main() {

	// Create an instance of the StackVM class
	StackVM vm;

	// Define a program as a vector of 32-bit integers
	std::vector<i32> prog{3, 4, 0x40000001, 5, 0x40000002, 3, 0x40000003, 2, 0x40000004, 0x40000000};

	// Load the program into the virtual machine
	vm.loadProgram(prog);

	// Run the program on the virtual machine
	vm.run();

	// Exit the program
	return 0;
}
