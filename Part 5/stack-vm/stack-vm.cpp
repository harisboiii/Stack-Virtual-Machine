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

// Constructor initializes memory vector to reserve space
StackVM::StackVM() {
	memory.reserve(1000000);
}

// Returns instruction type (first two bits of instruction)
i32 StackVM::getType(i32 instruction) {
	i32 type = 0xc0000000;
	type = (type & instruction) >> 30;
	return type;
}

// Returns instruction data (last 30 bits of instruction)
i32 StackVM::getData(i32 instruction) {
	i32 data = 0x3fffffff;
	data = data & instruction;
	return data;
}

// Fetches the next instruction from memory
void StackVM::fetch() {
	pc++;
}

// Decodes the current instruction
void StackVM::decode() {
	typ = getType(memory[pc]);
	dat = getData(memory[pc]);
}

// Executes the current instruction
void StackVM::execute() {
	if (typ == 0 || typ == 2) {
		sp++;
		memory[sp] = dat;
	} else {
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

// Runs the program by repeatedly fetching, decoding, and executing instructions
void StackVM::run() {
	pc -= 1;
	while (running == 1) {
		fetch();
		decode();
		execute();
		std::cout << "tos: " << memory[sp] << std::endl;
	}
}

// Loads a program into memory starting at the current program counter
void StackVM::loadProgram(std::vector<i32> prog) {
	for (i32 i = 0; i < prog.size(); i++) {
		memory[pc + i] = prog[i];
	}	
}
