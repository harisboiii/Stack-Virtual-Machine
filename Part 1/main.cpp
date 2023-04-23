#include "stack-vm.h"  // Include the StackVM header file

int main() {
	StackVM vm;  // Create a StackVM instance called "vm"
	
	// Create a program represented as a vector of integers
	// This program adds the values 3 and 4 and stores the result in memory location 0x40000000
	std::vector<i32> prog{3, 4, 0x40000001, 0x40000000};
	
	vm.loadProgram(prog);  // Load the program into the virtual machine
	vm.run();  // Run the virtual machine
	
	return 0;  // Return 0 to indicate successful program execution
}
