// This is a lexer class implementation that converts a string of characters into a list of tokens.
// Each token is a sequence of characters that represents a single meaningful entity in the input string.
// The class defines several helper functions for identifying and processing different types of characters.

#include "lexer.h"

// This function takes a string as input and returns a list of strings (tokens).
strings Lexer::lex(std::string s)
{
    // Initialize variables for tracking the current state of the lexer
    strings strlst;       // list to hold the tokens
    char lexeme[256];     // array to hold the characters of each token
    int i = 0;            // index of the current character in the input string
    int j = 0;            // index of the current character in the lexeme array
    State state = START;  // current state of the lexer
    int done = 0;         // flag to indicate when we have finished lexing the input string
    int len = s.length(); // length of the input string
    int balance = 0;      // counter to keep track of nested blocks
    // loop through each character in the input string
    while (i < len)
    {
        // determine the appropriate action based on the current state of the lexer
        switch (state)
        {
        case START:
            // if the current character is whitespace, skip it
            if (my_isspace(s[i]))
            {
                state = SKIP;
            }
            // if the current character is the start of a group, start reading the group
            else if (isgroup(s[i]))
            {
                if (s[i] == '"')
                {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                state = READBLOCK;
            }
            // if the current character is the start of a comment, skip the rest of the line
            else if (s[i] == '/' && s[i + 1] == '/')
            {
                i += 2;
                state = COMMENT;
            }
            // otherwise, start reading a character token
            else
            {
                state = READCHAR;
            }
            break;

        case READCHAR:
            // if the current character is whitespace, dump the current token and skip the whitespace
            if (my_isspace(s[i]))
            {
                state = DUMP;
            }
            // if the current character is an escape character, skip the next character
            else if (s[i] == '\\')
            {
                i += 2;
            }
            // if the current character is the start of a group, start reading the group
            else if (isgroup(s[i]))
            {
                if (s[i] == '"')
                {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                state = READBLOCK;
            }
            // if the current character is a special character, dump the current token and start a new token with the special character
            else if (isspecial(s[i]))
            {
                if (j == 0)
                {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                state = DUMP;
            }
            // if the current character is the start of a comment, skip the rest of the line
            else if (s[i] == '/' && s[i + 1] == '/')
            {
                i += 2;
                state = COMMENT;
            }
            // otherwise, add the current character to the current token and continue reading the token
            else
            {
                lexeme[j] = s[i];
                j++;
                i++;
            }
            break;
        // This block handles reading a block of characters delimited by `beg_char` and `end_char`
        case READBLOCK:
            if (s[i] == beg_char && s[i] != '"')
            {                     // Check if we have encountered the beginning of a block
                balance++;        // Increment the balance
                lexeme[j] = s[i]; // Add the current character to the lexeme buffer
                j++;              // Increment the index in the lexeme buffer
                i++;              // Increment the index in the input string
            }
            else if (s[i] == end_char)
            {                     // Check if we have encountered the end of a block
                balance--;        // Decrement the balance
                lexeme[j] = s[i]; // Add the current character to the lexeme buffer
                j++;              // Increment the index in the lexeme buffer
                i++;              // Increment the index in the input string
                if (balance <= 0)
                {                 // If the balance is zero or negative, we have reached the end of the block
                    state = DUMP; // Switch to the DUMP state to add the current token to the output stream
                }
            }
            else if (end_char == '"' && s[i] == '\\')
            { // If we are inside a double-quoted block and encounter an escape character
                // TODO: fix this to actually record the chars
                i += 2; // Skip over the next two characters (the escaped character and the following character)
            }
            else
            {                     // If we are still inside the block
                lexeme[j] = s[i]; // Add the current character to the lexeme buffer
                j++;              // Increment the index in the lexeme buffer
                i++;              // Increment the index in the input string
            }
            break;

        // This block skips over whitespace characters
        case SKIP:
            if (my_isspace(s[i]))
            {        // Check if the current character is whitespace
                i++; // Increment the index in the input string
            }
            else
            { // If we encounter a non-whitespace character, switch to the READCHAR state
                state = READCHAR;
            }
            break;

        // This block adds the current token (if any) to the output stream and resets the `j` variable
        case DUMP:
            if (j > 0)
            {                             // If we have encountered a non-empty token
                lexeme[j] = 0;            // Add a null-terminator to the end of the lexeme buffer
                strlst.push_back(lexeme); // Add the lexeme buffer to the output stream
                j = 0;                    // Reset the index in the lexeme buffer
            }
            state = START; // Switch back to the START state
            break;

        // This block skips over comment characters
        case COMMENT:
            if (s[i] != '\n')
            {        // Check if the current character is not a newline character
                i++; // Increment the index in the input string
            }
            else
            { // If we encounter a newline character, switch to the READCHAR state
                state = READCHAR;
            }
            break;

        // This block sets the index in the input string to the end of the string
        case END:
            i = len;
            break;
        }
    }
    // If we have encountered a non-empty token, add it to the output stream
    if (j > 0)
    {
        lexeme[j] = 0;            // Add a null-terminator to the end of the lexeme buffer
        strlst.push_back(lexeme); // Add the lexeme buffer to the output stream
    }

    return strlst;
}
// This function checks if a character is a whitespace character.
bool Lexer::my_isspace(char c)
{
    switch (c)
    {
    case '\n':
    case '\r':
    case '\t':
    case '\v':
    case ' ':
    case '\f':
        return true;
    default:
        return false;
    }
}

// This function checks if a character is a grouping character (e.g. "(" or ")").
bool Lexer::isgroup(char c)
{
    beg_char = c;
    switch (c)
    {
    case '"':
        end_char = '"';
        return true;
    case '(':
        end_char = ')';
        return true;
    case ')':
        return true;
    default:
        return false;
    }
}

// This function checks if a character is a special character (e.g. "[" or "]").
bool Lexer::isspecial(char c)
{
    switch (c)
    {
    case '[':
    case ']':
        return true;
    default:
        return false;
    }
}
