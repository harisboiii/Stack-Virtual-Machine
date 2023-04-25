#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>

// Define a new data type "byte" as an alias for uint8_t and "strings" as an alias for std::vector<std::string>
typedef uint8_t byte;
typedef std::vector<std::string> strings;

// Define an enumeration type "State" that represents the different states of the lexer
enum State : byte {
	START,      // Starting state
	READCHAR,   // Reading a character state
	READBLOCK,  // Reading a block of characters state
	SKIP,       // Skipping spaces state
	DUMP,       // Dumping characters state
	COMMENT,    // Comment state
	END         // End of input state
};

// The Lexer class
class Lexer {
	// Private member functions
	bool my_issspace(char c);   // Check if a character is a space character
	bool isspecial(char c);     // Check if a character is a special character
	bool isgroup(char c);       // Check if a character is a group character
	char end_char, beg_char;    // Ending and beginning characters for a block of characters
	public:
	// Public member functions
	strings lex(std::string s); // Tokenize a given string and return the resulting tokens as a vector of strings
};

#endif
