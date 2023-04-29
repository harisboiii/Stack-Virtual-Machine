#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>

// Define aliases for types
typedef uint8_t byte;
typedef std::vector<std::string> strings;

// Define the different states the lexer can be in
enum State : byte {
    START,      // Start of the input string
    READCHAR,   // Reading a character
    READBLOCK,  // Reading a block of characters
    SKIP,       // Skipping whitespace
    DUMP,       // Dumping a lexeme to the list
    COMMENT,    // Reading a comment
    END         // End of the input string
};

// Lexer class
class Lexer {
    char end_char, beg_char;    // The ending and beginning characters of a block
public:
    // Public function to perform lexical analysis on a string
    strings lex(std::string s);

private:
    // Private function to check if a character is whitespace
    bool my_isspace(char c);

    // Private function to check if a character is a special character
    bool isspecial(char c);

    // Private function to check if a character is a group character
    bool isgroup(char c);
};

#endif
