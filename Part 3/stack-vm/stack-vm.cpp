// Include the header file for the StackVM class
#include "stack-vm.h"

/*

Instruction format
header: 2 bits
data: 30 bits
header format:
0 => positive integer
1 => primitive instruction
2 => negative integer
3 => undefined
*/
// Constructor for StackVM class, reserve memory of size 1000000
StackVM::StackVM()
{
    memory.reserve(1000000);
}

// Get the type of instruction using bit manipulation
i32 StackVM::getType(i32 instruction)
{
    i32 type = 0xc0000000;
    type = (type & instruction) >> 30;
    return type;
}

// Get the data of instruction using bit manipulation
i32 StackVM::getData(i32 instruction)
{
    i32 data = 0x3fffffff;
    data = data & instruction;
    return data;
}

// Increment the program counter
void StackVM::fetch()
{
    pc++;
}

// Decode the instruction and get its type and data
void StackVM::decode()
{
    typ = getType(memory[pc]);
    dat = getData(memory[pc]);
}

// Execute the instruction
void StackVM::execute()
{
    // If the type of instruction is 0 or 2, push the data onto the stack
    if (typ == 0 || typ == 2)
    {
        sp++;
        memory[sp] = dat;
    }
    // Otherwise, perform a primitive operation
    else
    {
        doPrimitive();
    }
}

// Perform a primitive operation based on the data of the instruction
void StackVM::doPrimitive()
{
    switch (dat)
    {
    case 0: // halt
        std::cout << "halt" << std::endl;
        running = 0;
        break;
    case 1: // add
        std::cout << "add " << memory[sp - 1] << " " << memory[sp] << std::endl;
        memory[sp - 1] = memory[sp - 1] + memory[sp];
        sp--;
        break;
    case 2: // sub
        std::cout << "sub " << memory[sp - 1] << " " << memory[sp] << std::endl;
        memory[sp - 1] = memory[sp - 1] - memory[sp];
        sp--;
        break;
    case 3: // mul
        std::cout << "mul " << memory[sp - 1] << " " << memory[sp] << std::endl;
        memory[sp - 1] = memory[sp - 1] * memory[sp];
        sp--;
        break;
    case 4: // div
        std::cout << "div " << memory[sp - 1] << " " << memory[sp] << std::endl;
        memory[sp - 1] = memory[sp - 1] / memory[sp];
        sp--;
        break;
    }
}

// Run the program
void StackVM::run()
{
    pc -= 1; // Set the program counter to -1
    while (running == 1)
    {
        fetch();                                         // Increment the program counter
        decode();                                        // Decode the instruction
        execute();                                       // Execute the instruction
        std::cout << "tos: " << memory[sp] << std::endl; // Print the top of stack
    }
}

// Load a program into memory

void StackVM::loadProgram(std::vector<i32> prog)
{
    for (i32 i = 0; i < prog.size(); i++)
    {
        memory[pc + i] = prog[i];
    }
}
