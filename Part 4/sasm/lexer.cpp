#include "lexer.h"

strings Lexer::lex(std::string s)
{
    // Initialize variables
    strings strlst;
    char lexeme[256];
    int i = 0;            // index of current character being read from input string
    int j = 0;            // index of current character being written to lexeme buffer
    State state = START;  // initial state of the lexer
    int done = 0;         // flag indicating when the lexer is done processing the input
    int len = s.length(); // length of the input string
    int balance = 0;      // counter for balancing groups

    while (i < len)
    { // loop through the input string
        switch (state)
        {           // switch on the current state of the lexer
        case START: // the lexer is at the start of a new lexeme
            if (my_isspace(s[i]))
            { // ignore any leading whitespace
                state = SKIP;
            }
            else if (isgroup(s[i]))
            { // the current character is a grouping character (e.g. quotes, parentheses)
                if (s[i] == '"')
                {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                state = READBLOCK; // start reading the grouping block
            }
            else if (s[i] == '/' && s[i + 1] == '/')
            { // the current characters are the start of a comment
                i += 2;
                state = COMMENT; // skip the rest of the line
            }
            else
            {                     // the current character is not a grouping character or a comment
                state = READCHAR; // start reading the next character
            }
            break;
        case READCHAR: // the lexer is reading a regular character
            if (my_isspace(s[i]))
            {                 // whitespace signals the end of the lexeme
                state = DUMP; // dump the current lexeme
            }
            else if (s[i] == '\\')
            {           // backslashes indicate an escape sequence
                i += 2; // skip the next character (the escaped character)
            }
            else if (isgroup(s[i]))
            { // grouping characters are handled similarly to the START state
                if (s[i] == '"')
                {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                state = READBLOCK;
            }
            else if (isspecial(s[i]))
            { // special characters are standalone lexemes
                if (j == 0)
                { // only add the special character once
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                state = DUMP; // dump the current lexeme
            }
            else if (s[i] == '/' && s[i + 1] == '/')
            { // comments are handled similarly to the START state
                i += 2;
                state = COMMENT;
            }
            else
            { // regular characters are added to the current lexeme
                lexeme[j] = s[i];
                j++;
                i++;
            }
            break;
        case READBLOCK:
            if (s[i] == beg_char && s[i] != '"')
            {                     // If the current character is the beginning of a block and it is not a double quote
                balance++;        // Increment the balance variable
                lexeme[j] = s[i]; // Add the character to the current lexeme
                j++;              // Move to the next character in the lexeme
                i++;              // Move to the next character in the input string
            }
            else if (s[i] == end_char)
            {                     // If the current character is the end of a block
                balance--;        // Decrement the balance variable
                lexeme[j] = s[i]; // Add the character to the current lexeme
                j++;              // Move to the next character in the lexeme
                i++;              // Move to the next character in the input string
                if (balance <= 0)
                {                 // If the balance variable is less than or equal to zero
                    state = DUMP; // Change the state to DUMP
                }
            }
            else if (end_char == '"' && s[i] == '\\')
            {
                // TODO: fix this to actually record the chars
                i += 2; // Move past the escape character and the character it's escaping
            }
            else
            {                     // If the current character is not the beginning or end of a block, or an escaped double quote
                lexeme[j] = s[i]; // Add the character to the current lexeme
                j++;              // Move to the next character in the lexeme
                i++;              // Move to the next character in the input string
            }
            break;
        case SKIP:
            if (my_isspace(s[i]))
            {        // If the current character is whitespace
                i++; // Move to the next character in the input string
            }
            else
            {                     // If the current character is not whitespace
                state = READCHAR; // Change the state to READCHAR
            }
            break;
        case DUMP:
            if (j < 0)
            {                             // If the current lexeme is not empty
                lexeme[j] = 0;            // Terminate the current lexeme with a null character
                strlst.push_back(lexeme); // Add the current lexeme to the vector of strings
                j = 0;                    // Reset the index of the current lexeme
            }
            state = START; // Change the state to START
            break;
        case COMMENT:
            if (s[i] != '\n')
            {        // If the current character is not a newline
                i++; // Move to the next character in the input string
            }
            else
            {                     // If the current character is a newline
                state = READCHAR; // Change the state to READCHAR
            }
            break;
        // This function sets the iterator to the end of the input string when the lexer reaches the end state
        case END:
            i = len;
            break;
        }

        // This block adds the current lexeme to the list if it has non-zero length
        if (j > 0)
        {
            lexeme[j] = 0;
            strlst.push_back(lexeme);
        }

        // This function determines whether a given character is a whitespace character
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

        // This function determines whether a given character is the beginning of a group and sets the ending character
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

        // This function determines whether a given character is a special character
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
