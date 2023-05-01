#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>

typedef uint8_t byte;
typedef std::vector<std::string> strings;

// Enumeration of all possible states for the Lexer to be in
enum State : byte {
	START,      // Initial state
	READCHAR,   // Reading in a character
	READBLOCK,  // Reading in a block (e.g. a string or a parenthesis group)
	SKIP,       // Skipping over whitespace
	DUMP,       // Dumping a lexeme to the list of tokens
	COMMENT,    // Reading in a comment
	END         // Reached the end of the input
};

class Lexer {
	// Determines if a character is considered whitespace by the lexer
	bool my_isspace(char c);

	// Determines if a character is a special character (e.g. brackets)
	bool isspecial(char c);

	// Determines if a character is the beginning of a block (e.g. string or parenthesis group)
	bool isgroup(char c);

	// Variables to keep track of the beginning and ending characters of a block
	char end_char, beg_char;

	public:
		// Lexes a given string into a list of tokens
		strings lex(std::string s);
};

#endif
