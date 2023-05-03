#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>

typedef uint8_t byte;
typedef std::vector<std::string> strings;

// Enum to represent the different states of the lexer
enum State : byte {
	START,
	READCHAR,
	READBLOCK,
	SKIP,
	DUMP,
	COMMENT,
	END
};

class Lexer {
	// Helper function to check if a character is a whitespace character
	bool my_isspace(char c);
	// Helper function to check if a character is a special character
	bool isspecial(char c);
	// Helper function to check if a character is a grouping character
	bool isgroup(char c);
	// Variables to keep track of the beginning and end grouping characters
	char end_char, beg_char;
	public:
	// Function to perform lexical analysis on a string and return a vector of strings (tokens)
	strings lex(std::string s);
};

#endif
