#include "stack-vm.h"

/*
 * Instruction format
 * header: 2 bits
 * data: 30 bits
 *
 * header format:
 * 0 => positive integer
 * 1 => primitive instruction
 * 2 => negative integer
 * 3 => undefined
 * */

// Define the StackVM class
class StackVM {
public:
    // Constructor that initializes the memory vector with a default size of 1000000
    StackVM();
    // Member functions that perform different parts of the execution process
    i32 getType(i32 instruction); // Returns the type of an instruction
    i32 getData(i32 instruction); // Returns the data associated with an instruction
    void fetch(); // Increments the program counter (pc)
    void decode(); // Decodes the instruction at the current pc into type and data values
    void execute(); // Executes the instruction at the current pc
    void doPrimitive(); // Executes the primitive instruction currently on top of the stack
    void run(); // Fetches, decodes, and executes instructions until the program halts
    void loadProgram(std::vector<i32> prog); // Loads a program into memory starting at the current pc

private:
    std::vector<i32> memory; // Memory space of the virtual machine
    i32 pc = 100; // Program counter
    i32 sp = 0; // Stack pointer
    i32 running = 1; // Flag to indicate whether the program is still running
    i32 typ = 0; // Type of the current instruction
    i32 dat = 0; // Data associated with the current instruction
};

// Constructor that initializes the memory vector with a default size of 1000000
StackVM::StackVM() {
    memory.reserve(1000000);
}

// Returns the type of an instruction
i32 StackVM::getType(i32 instruction) {
    i32 type = 0xc0000000;
    type = (type & instruction) >> 30;
    return type;
}

// Returns the data associated with an instruction
i32 StackVM::getData(i32 instruction) {
    i32 data = 0x3fffffff;
    data = data & instruction;
    return data;
}

// Increments the program counter (pc)
void StackVM::fetch() {
    pc++;
}

// Decodes the instruction at the current pc into type and data values
void StackVM::decode() {
    typ = getType(memory[pc]);
    dat = getData(memory[pc]);
}

// Executes the instruction at the current pc
void StackVM::execute() {
    if (typ == 0 || typ == 2) {
        sp++;
        memory[sp] = dat;
    } else {
        doPrimitive();
    }
}

// Executes the primitive instruction currently on top of the stack
void StackVM::doPrimitive() {
    switch (dat) {
        case 0: // halt
            std::cout << "halt" << std::endl;
            running = 0;
            break;
        case 1: // add
            std::cout << "add " << memory[sp - 1] << " " << memory[sp] << std::endl;
            memory[sp - 1] = memory[sp - 1] + memory[sp];
            sp--;
            break;
    }
}

// Fetches, decodes, and executes instructions until the program halts
void StackVM::run() {
    pc -= 1;
while (running == 1) {
	fetch(); // Fetch the next instruction
	decode(); // Decode the fetched instruction
	execute(); // Execute the decoded instruction
	std::cout << "tos: " << memory[sp] << std::endl; // Print the top of stack value
	}
}

// This function loads the program into the VM's memory by copying each program instruction into memory starting at the program counter
void StackVM::loadProgram(std::vector<i32> prog) {
for (i32 i = 0; i < prog.size(); i++) {
memory[pc + i] = prog[i];
	}
}
