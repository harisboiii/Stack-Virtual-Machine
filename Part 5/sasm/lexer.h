// This line includes the header file "iostream"
// which provides input and output functionality
#include <iostream>

// This line includes the header file "vector"
// which provides a dynamic array-like container that can be resized
#include <vector>

// This line defines a new type called "byte" which is an alias for the built-in
// unsigned integer type uint8_t
typedef uint8_t byte;

// This line defines a new type called "strings" which is an alias for a vector
// of strings (i.e., a vector where each element is a string)
typedef std::vector<std::string> strings;

// This line defines a new enumeration type called "State" which represents
// the different states the lexer can be in
enum State : byte {
    START,
    READCHAR,
    READBLOCK,
    SKIP,
    DUMP,
    COMMENT,
    END
};

// This line defines a new class called "Lexer"
class Lexer {
    // These two functions are private member functions of the Lexer class
    bool my_isspace(char c);
    bool isspecial(char c);
    
    // This function is also a private member function of the Lexer class
    bool isgroup(char c);
    
    // These two variables are public member variables of the Lexer class
    // that specify the beginning and ending characters of a block
    char end_char, beg_char;
    
    // This function is a public member function of the Lexer class that
    // takes a string as input and returns a vector of strings
    public:
    strings lex(std::string s);
};

// This line ends the "#ifndef" preprocessor directive that checks whether
// "LEXER_H" has been defined, and if not, defines it to prevent multiple
// definitions of the same header file
#endif
