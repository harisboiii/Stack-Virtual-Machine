#include "stack-vm.h"

int main() {
	StackVM vm;  // create an instance of StackVM
	// create a vector of instructions, in this case adding, subtracting, multiplying, and dividing integers
	std::vector<i32> prog{3, 4, 0x40000001, 5, 0x40000002, 3, 0x40000003, 2, 0x40000004, 0x40000000};
	vm.loadProgram(prog);  // load the program into the StackVM instance
	vm.run();  // execute the program in the StackVM instance
	return 0;
}
