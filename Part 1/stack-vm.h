// This header file defines a StackVM class that emulates a simple stack-based virtual machine

#ifndef STACK_VM_H
#define STACK_VM_H

#include <iostream>
#include <vector>

// type definitions
typedef int32_t i32;

// StackVM class declaration
class StackVM {
// Private member variables
i32 pc = 100; // program counter
i32 sp = 0; // stack pointer                    //CREATING REGISTERS FOR OUR VIRUAL MACHINE
std::vector<i32> memory; // memory array
i32 typ = 0; // instruction type
i32 dat = 0; // instruction data
i32 running = 1; // flag to indicate whether the program is still running
	
// Private member functions
i32 getType(i32 instruction); // Extracts the instruction type from an instruction word
i32 getData(i32 instruction); // Extracts the instruction data from an instruction word
void fetch(); // Fetches the next instruction from memory
void decode(); // Decodes the fetched instruction
void execute(); // Executes the decoded instruction
void doPrimitive(); // Executes a primitive instruction

public:
// Public member functions
StackVM(); // Constructor function
void run(); // Executes the loaded program
void loadProgram(std::vector<i32> prog); // Loads a program into memory

};

#endif
