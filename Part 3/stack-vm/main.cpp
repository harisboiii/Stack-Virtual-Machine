
#include "stack-vm.h" // Include the header file for the StackVM class

int main() {
	StackVM vm; // Create an instance of the StackVM class
	std::vector<i32> prog{3, 4, 0x40000001, 5, 0x40000002, 3, 0x40000003, 2, 0x40000004, 0x40000000}; // Create a vector of integers to represent the program
	vm.loadProgram(prog); // Load the program into the virtual machine
	vm.run(); // Run the program
	return 0; // Return 0 to indicate successful execution
}
