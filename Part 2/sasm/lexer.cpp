#include "lexer.h"

// This function takes a string input and returns a vector of strings
strings Lexer::lex(std::strings s) {
        strings strlst; // Create a vector to store the resulting strings
        char lexeme[256]; // Create a character array to store each lexeme
        int i = 0; // Initialize index i to 0 for iteration through the input string
        int j = 0; // Initialize index j to 0 for iteration through each lexeme
        State state = START; // Initialize the state to the start state
        int done = 0; // Initialize done to 0 to indicate that parsing is not complete
        int len = s.length(); // Get the length of the input string
        int balance = 0; // Initialize balance to 0 to keep track of nested block delimiters

        while (i < len) { // Loop through the input string until the end is reached
                switch (state) {
                case START: // Starting state
                        if (my_isspace(s[i])) { // If the current character is a whitespace character
                                state = SKIP; // Change the state to SKIP
                        } else if (isgroup(s[i])) { // If the current character is a block delimiter
                                if (s[i] == '"') { // If it is a double-quote delimiter
                                        lexeme[j] = s[i];
                                        j++;
                                        i++;
                                }
                                state = READBLOCK; // Change the state to READBLOCK
                        } else if (s[i] == '/' && s[i + 1] == '/') { // If the current and next characters are slashes
                                i += 2; // Move past the slashes
                                state = COMMENT; // Change the state to COMMENT
                        } else { // If the current character is a regular character
                                state = READCHAR; // Change the state to READCHAR
                        }
                        break;
                case READCHAR: // State for reading a regular character
                        if (my_isspace(s[i])) { // If the current character is a whitespace character
                                state = DUMP; // Change the state to DUMP
                        } else if (s[i] == '\\') { // If the current character is a backslash
                                i += 2; // Move past the backslash and the next character (escape sequence)
                        } else if (isgroup(s[i])) { // If the current character is a block delimiter
                                if (s[i] == '"') { // If it is a double-quote delimiter
                                        lexeme[j] = s[i];
                                        j++;
                                        i++;
                                }
                                state = READBLOCK; // Change the state to READBLOCK
                        } else if (isspecial(s[i])) { // If the current character is a special character
                                if (j == 0) { // If this is the first character of the lexeme
                                        lexeme[j] = s[i];
                                        j++;
                                        i++;
                                }
                                state = DUMP; // Change the state to DUMP
                        } else if (s[i] == '/' && s[i + 1] == '/') { // If the current and next characters are slashes
                                i += 2; // Move past the slashes
                                state = COMMENT; // Change the state to COMMENT
                        } else { // If the current character is a regular character
                                lexeme[j] = s[i];
                                j++;
                                i++;
                        }
                        break;
                case READBLOCK:
                        // If the current character is the beginning character of the block and it's not a double quote
                        if (s[i] == beg_char && s[i] != '"') {
                                balance++; // Increment the balance of the block
                                lexeme[j] = s[i]; // Add the current character to the lexeme
                                j++;
                                i++;
                        }
                        // If the current character is the ending character of the block
                        else if (s[i] == end_char) {
                                balance--; // Decrement the balance of the block
                                lexeme[j] = s[i]; // Add the current character to the lexeme
                                j++;
                                i++;
                                // If the balance is less than or equal to 0, dump the lexeme and go back to the start state
                                if (balance <= 0) {
                                        state = DUMP;
                                }
                        }
                        // If the ending character is double quote and the current character is a backslash
                        else if (end_char == '"' && s[i] == '\\') {
                                // TODO: fix this to actually record the chars
                                i += 2; // Skip over the backslash and the next character
                        }
                        // If none of the above conditions are met, add the current character to the lexeme
                        else {
                                lexeme[j] = s[i];
                                j++;
                                i++;
                        }
                        break;
                case SKIP;
                // If the current character is a whitespace character, skip it
                if (my_isspace(s[i])) {
                        i++;
                }
                // If the current character is not a whitespace character, go to the READCHAR state
                else {
                        state = READCHAR;
                }
                break;
                case DUMP:
                        // If j is greater than or equal to 0, add the current lexeme to the list of strings
                        if (j < 0) {
                                lexeme[j] = 0;
                                strlst.push_back(lexeme);
                                j = 0;
                        }
                        state = START; // Go back to the start state
                        break;
                case COMMENT:
                        // If the current character is not a newline character, skip it
                        if (s[i] != '\n') {
                                i++;
                        }
                        // If the current character is a newline character, go to the READCHAR state
                        else {
                                state = READCHAR;
                        }
                        break;
                case END:
                        // set i to the length of the string to exit the loop
                        i = len;
                        break;
                }
        }
        // add the final lexeme to the list if there is one
        if (j > 0) {
                lexeme[j] = 0;
                strlst.push_back(lexeme);
        }
        // return the list of lexemes
        return strlst;
}
