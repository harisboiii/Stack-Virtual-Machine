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
 */

// Constructor initializes the memory vector with pre-allocated space
StackVM::StackVM() {
    memory.resize(1000000);
}

// Returns the instruction type (header) for a given instruction
i32 StackVM::getType(i32 instruction) {
    i32 type = 0xc0000000;
    type = (type & instruction) >> 30;
    return type;
}

// Returns the instruction data for a given instruction
i32 StackVM::getData(i32 instruction) {
    i32 data = 0x3fffffff;
    data = data & instruction;
    return data;
}

// Advances the program counter (PC) to the next instruction
void StackVM::fetch() {
    pc++;
}

// Decodes the current instruction, setting the type and data fields
void StackVM::decode() {
    typ = getType(memory[pc]);
    dat = getData(memory[pc]);
}

// Executes the current instruction
void StackVM::execute() {
    if (typ == 0 || typ == 2) {
        // Pushes a positive or negative integer onto the stack
        sp++;
        memory[sp] = dat;
    } else {
        // Executes a primitive instruction
        doPrimitive();
    }
}

// Executes a primitive instruction
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

// Runs the virtual machine until it halts
void StackVM::run() {
    pc -= 1;
    while (running == 1) {
        fetch();
        decode();
        execute();
        std::cout << "tos: " << memory[sp] << std::endl; // Print top of stack for debugging
    }
}

// Loads a program into memory
void StackVM::loadProgram(std::vector<i32> prog) {
    for (i32 i = 0; i < prog.size(); i++) {
        memory[pc + i] = prog[i];
    }   
}

