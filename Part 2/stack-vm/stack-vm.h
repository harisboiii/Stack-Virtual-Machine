#ifndef STACK_VM_H
#define STACK_VM_H

#include <iostream>
#include <vector>

typedef int32_t i32; // Define a new type alias for a 32-bit integer named i32.

class StackVM {
    i32 pc = 100; // Initialize program counter to 100.
    i32 sp = 0; // Initialize stack pointer to 0.
    std::vector<i32> memory; // Create a vector to store the memory.
    i32 typ = 0; // Initialize opcode to 0.
    i32 dat = 0; // Initialize operand to 0.
    i32 running = 1; // Set running to 1 to start the virtual machine.
	
    i32 getType(i32 instruction); // Private function to get the opcode of an instruction.
    i32 getData(i32 instruction); // Private function to get the operand of an instruction.
    void fetch(); // Private function to fetch the next instruction.
    void decode(); // Private function to decode the fetched instruction.
    void execute(); // Private function to execute the decoded instruction.
    void doPrimitive(); // Private function to perform a primitive operation.
	
public:
    StackVM(); // Constructor for the StackVM class.
    void run(); // Public function to start the virtual machine.
    void loadProgram(std::vector<i32> prog); // Public function to load a program into the virtual machine memory.
};

#endif
