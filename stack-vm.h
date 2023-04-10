// Include guard to prevent multiple inclusions of this header
#ifndef STACK_VM_H
#define STACK_VM_H

// Include necessary libraries
#include <iostream>
#include <vector>

// Type definitions
typedef int32_t i32;

// Definition of the StackVM class
class StackVM {
	// Private member variables
	i32 pc = 100; // Program counter
	i32 sp = 0; // Stack pointer
	std::vector<i32> memory; // Memory of the virtual machine
	i32 typ = 0; // Type of the current instruction
	i32 dat = 0; // Data of the current instruction
	i32 running = 1; // Running state of the virtual machine
	
	// Private member functions
	i32 getType(i32 instruction); // Extracts the type of the given instruction
	i32 getData(i32 instruction); // Extracts the data of the given instruction
	void fetch(); // Fetches the next instruction from memory
	void decode(); // Decodes the fetched instruction into type and data
	void execute(); // Executes the current instruction
	void doPrimitive(); // Helper function to execute primitive instructions
	
	// Public member functions
	public:
	// Constructor
	StackVM();
	
	// Runs the virtual machine by repeatedly fetching, decoding, and executing instructions
	void run();
	
	// Loads the given program into memory
	void loadProgram(std::vector<i32> prog);
};

// End of include guard
#endif

