#ifndef STACK_VM_H // if STACK_VM_H is not defined
#define STACK_VM_H // define STACK_VM_H

#include <iostream> // include the standard input/output stream library
#include <vector> // include the vector library

// define the type i32 to be a 32-bit integer
typedef int32_t i32;

// define the StackVM class
class StackVM {
	// define private data members
	i32 pc = 100; // initialize the program counter to 100
	i32 sp = 0; // initialize the stack pointer to 0
	std::vector<i32> memory; // initialize an empty memory vector
	i32 typ = 0; // initialize the type value to 0
	i32 dat = 0; // initialize the data value to 0
	i32 running = 1; // set the running flag to 1 (true)
	
	// define private member functions
	i32 getType(i32 instruction); // get the type value of an instruction
	i32 getData(i32 instruction); // get the data value of an instruction
	void fetch(); // fetch the next instruction from memory
	void decode(); // decode the fetched instruction
	void execute(); // execute the decoded instruction
	void doPrimitive(); // perform primitive operations
	
	// define public member functions
	public:
	StackVM(); // default constructor
	void run(); // execute the program
	void loadProgram(std::vector<i32> prog); // load a program into memory
};

#endif // end of the header file inclusion guard
