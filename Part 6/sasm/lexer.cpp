#include "lexer.h"

strings Lexer::lex(std::string s) {
    // list to hold the individual tokens
    strings strlst;
    // buffer to hold the current token being processed
    char lexeme[256];
    int i = 0;
    int j = 0;
    // initial state of the lexer
    State state = START;
    int done = 0;
    // length of input string
    int len = s.length();
    // counter to keep track of open brackets
    int balance = 0;

    while(i < len) {
        switch(state) {
        // the lexer is at the beginning of a new token
        case START:
            if (my_isspace(s[i])) {
                // if the current character is whitespace, skip it
                state = SKIP;
            } else if (isgroup(s[i])) {
                // if the current character is a group character, start reading the block
                if(s[i] == '"') {
                    // if it's a double-quote, include it in the token
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                state = READBLOCK;
            } else if (s[i] == '/' && s[i + 1] == '/') {
                // if the current characters are "//", skip the entire line as a comment
                i += 2;
                state = COMMENT;
            } else {
                // otherwise, start reading a character token
                state = READCHAR;
            }
            break;
        // the lexer is reading a character token
        case READCHAR:
            if (my_isspace(s[i])) {
                // if the current character is whitespace, dump the token and return to the start state
                state = DUMP;
            } else if (s[i] == '\\') {
                // if the current character is a backslash, skip the next character
                i += 2;
            } else if (isgroup(s[i])) {
                // if the current character is a group character, start reading the block
                if (s[i] == '"') {
                    // if it's a double-quote, include it in the token
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                state = READBLOCK;
            } else if (isspecial(s[i])) {
                // if the current character is a special character (e.g., '[' or ']'), include it in the token
                if (j == 0) {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                state = DUMP;
            } else if (s[i] == '/' && s[i + 1] == '/') {
                // if the current characters are "//", skip the entire line as a comment
                i += 2;
                state = COMMENT;
            } else {
                // otherwise, include the character in the token
                lexeme[j] = s[i];
                j++;
                i++;
            }
            break;
        // the lexer is reading a block token (e.g., a string enclosed in quotes or parentheses)
        case READBLOCK:
			// Check if the current character is the beginning character of a block and not a double quote
			if (s[i] == beg_char && s[i] != '"') {
				// Increment balance variable to keep track of nested blocks
				balance++;
				// Add current character to current lexeme
				lexeme[j] = s[i];
				j++;
				i++;
			} 
			// Check if the current character is the ending character of a block
			else if (s[i] == end_char) {
				// Decrement balance variable to keep track of nested blocks
				balance--;
				// Add current character to current lexeme
				lexeme[j] = s[i];
				j++;
				i++;
				// Check if there are no more nested blocks
				if (balance <= 0) {
					// Move to the DUMP state to add current lexeme to strlst
					state = DUMP;
				}
			} 
			// Check if the current character is a backslash within a double quote block
			else if (end_char == '"' && s[i] == '\\') {
				// TODO: fix this to actually record the chars
				// Skip current and next character, as the next character is escaped
				i += 2;
			} 
			// Otherwise, add current character to current lexeme
			else {
				lexeme[j] = s[i];
				j++;
				i++;
			}
			break;
		case SKIP:
			// Check if the current character is a space character
			if (my_isspace(s[i])) {
				// Skip the space character
				i++;
			} 
			// Move to the READCHAR state to add current non-space character to lexeme
			else {
				state = READCHAR;
			}
			break;
		case DUMP:
			// Check if the current lexeme is not empty
			if (j > 0) {
				// Terminate current lexeme with null character and add it to strlst
				lexeme[j] = 0;
				strlst.push_back(lexeme);
				// Reset j to 0 for next lexeme
				j = 0;
			}
			// Move to the START state to start a new lexeme
			state = START;
			break;
		case COMMENT:
			// Check if the current character is not a new line character
			if (s[i] != '\n') {
				// Skip current character
				i++;
			} 
			// Move to the READCHAR state to add next non-comment character to lexeme
			else {
				state = READCHAR;
			}
			break;
		case END:
			// Set i to len to exit loop
			i = len;
			break;
		}
	}
	// Check if the last lexeme is not empty
	if (j > 0) {
		// Terminate last lexeme with null character and add it to strlst
		lexeme[j] = 0;
		strlst.push_back(lexeme);
	}
	// Return list of lexemes
	return strlst;
}

// This function defines what a space character is
// this function allows us to define what a space is
bool Lexer::my_isspace(char c) {
	switch(c) {
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
bool Lexer::isgroup(char c) {
	beg_char = c;
	switch(c) {
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
bool Lexer::isspecial(char c) {
	switch(c) {
		case '[':
		case ']':
			return true;
		default:
			return false;
	}
}
