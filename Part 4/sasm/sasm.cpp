#include <iostream>
#include <fstream>
#include "lexer.h"

typedef uint32_t i32; // Define i32 as an unsigned 32-bit integer

using namespace std;

// Function prototypes
vector<i32> compileToInstructions(strings s);
bool isInteger(string s);
bool isPrimimitive(string s);
i32 mapToNumber(string s);

int main(int argc, char *argv[]) {
	// Check if the program was run with exactly one argument
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <sasm-filename>" << endl;
		exit(1); // Exit with an error code
	}

	// Open the input file
	ifstream infile;
	infile.open(argv[1]);
	if (!infile.is_open()) {
		cout << "Error: could not open [" << argv[1] << "]" << endl;
		exit(1); // Exit with an error code
	}

	// Read the entire file into a string
	string line;
	string contents;
	while (getline(infile, line)) {
		contents += line + "\n";
	}
	infile.close(); // Close the input file

	// Tokenize the input string using the Lexer class
	Lexer lexer;
	strings lexemes = lexer.lex(contents);

	// Convert the tokens to machine instructions
	vector<i32> instructions = compileToInstructions(lexemes);

	// Write the machine instructions to a binary file
	ofstream ofile;
	ofile.open("out.bin", ios::binary);
	for (i32 i = 0; i < instructions.size(); i++) {
		ofile.write(reinterpret_cast<char *>(&instructions[i]), sizeof(i32));
	}
	ofile.close(); // Close the output file

	return 0; // Exit with success
}

// Convert an array of tokens to an array of machine instructions
vector<i32> compileToInstructions(strings s) {
	vector<i32> instructions;
	for (i32 i = 0; i < s.size(); i++) {
		if (isInteger(s[i])) { // If the token is an integer, convert it to a machine word
			instructions.push_back(stoi(s[i]));
		} else {
			i32 instruction = mapToNumber(s[i]); // Otherwise, map the token to a machine instruction
			if (instruction != -1) {
				instructions.push_back(instruction);
			} else {
				cout << "Error: Invalid instruction [" << s[i] << "]" << endl;
			}
		}
	}
	return instructions;
}

// Check if a string represents an integer
bool isInteger(string s) {
	for (i32 i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

// Check if a string represents a primitive operation (+, -, *, /)
bool isPrimimitive(string s) {
	return (s == "+" || s == "-" || s == "*" || s == "/");
}

// Map a string to a machine instruction
i32 mapToNumber(string s) {
	if (s == "+") {
		return 0x40000001;
	} else if (s == "-") {
		return 0x40000002;
	} else if (s == "*") {
		return 0x40000003;
	} else if (s == "/") {
		return 0x40000004;
	}
	return -1; // Invalid instruction
}
