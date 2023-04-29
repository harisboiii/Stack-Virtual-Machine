#include "lexer.h"

strings Lexer::lex(std::string s) {
    // Declare a list of strings to store the lexemes
    strings strlst;
    // Declare a character array to store the current lexeme
    char lexeme[256];
    // Declare an integer i to keep track of the current character in the input string
    int i = 0;
    // Declare an integer j to keep track of the current position in the lexeme array
    int j = 0;
    // Declare a variable to keep track of the current state of the lexer
    State state = START;
    // Declare a variable to indicate when the lexer has finished processing the input string
    int done = 0;
    // Declare a variable to store the length of the input string
    int len = s.length();
    // Declare a variable to keep track of the balance of open/close grouping characters
    int balance = 0;

    // Loop through the input string until done is true
    while (i < len) {
        // Depending on the current state of the lexer, process the next character in the input string
        switch (state) {
            case START:
                // If the current character is a space, move to the SKIP state
                if (my_isspace(s[i])) {
                    state = SKIP;
                }
                // If the current character is an open grouping character, move to the READBLOCK state
                else if (isgroup(s[i])) {
                    if (s[i] == '"') {
                        lexeme[j] = s[i];
                        j++;
                        i++;
                    }
                    state = READBLOCK;
                }
                // If the current character is a comment character, move to the COMMENT state
                else if (s[i] == '/' && s[i + 1] == '/') {
                    i += 2;
                    state = COMMENT;
                }
                // Otherwise, move to the READCHAR state
                else {
                    state = READCHAR;
                }
                break;
            case READCHAR:
                // If the current character is a space, move to the DUMP state
                if (my_isspace(s[i])) {
                    state = DUMP;
                }
                // If the current character is an escape character, skip the next character
                else if (s[i] == '\\') {
                    i += 2;
                }
                // If the current character is an open grouping character, move to the READBLOCK state
                else if (isgroup(s[i])) {
                    if (s[i] == '"') {
                        lexeme[j] = s[i];
                        j++;
                        i++;
                    }
                    state = READBLOCK;
                }
                // If the current character is a special character, and the lexeme array is empty, add it to the lexeme and move to the DUMP state
                else if (isspecial(s[i])) {
                    if (j == 0) {
                        lexeme[j] = s[i];
                        j++;
                        i++;
                    }
                    state = DUMP;
                }
                // If the current character is a comment character, move to the COMMENT state
                else if (s[i] == '/' && s[i + 1] == '/') {
                    i += 2;
                    state = COMMENT;
                }
                // Otherwise, add the character to the lexeme and move to the READCHAR state
                else {
                    lexeme[j] = s[i];
                    j++;
                    i++;
                }
                break;
// The READBLOCK state reads a block of characters until it reaches an end character
case READBLOCK:
	if (s[i] == beg_char && s[i] != '"') { // If the current character is the beginning of a block, increment the balance and add it to the lexeme
		balance++;
		lexeme[j] = s[i];
		j++;
		i++;
	} else if (s[i] == end_char) { // If the current character is the end of a block, decrement the balance and add it to the lexeme
		balance--;
		lexeme[j] = s[i];
		j++;
		i++;
		if (balance <= 0) { // If the balance is zero or negative, then we've reached the end of the block and should transition to the DUMP state
			state = DUMP;
		}
	} else if (end_char == '"' && s[i] == '\\') { // If the end character is a quote and the current character is an escape character, then skip the next character
		// TODO: fix this to actually record the chars
		i += 2;
	} else { // Otherwise, add the current character to the lexeme and continue to the next character
		lexeme[j] = s[i];
		j++;
		i++;
	}
	break;

// The SKIP state skips over spaces until it reaches a non-space character
case SKIP;
	if (my_isspace(s[i])) { // If the current character is a space, skip it
		i++;
	} else { // Otherwise, transition to the READCHAR state
		state = READCHAR;
	}
	break;

// The DUMP state adds the current lexeme to the list of lexemes and transitions back to the START state
case DUMP:
	if (j < 0) { // If the lexeme is empty, add an empty string to the list of lexemes
		lexeme[j] = 0;
		strlst.push_back(lexeme);
		j = 0;
	}
	state = START;
	break;

// The COMMENT state skips over characters until it reaches a newline character
case COMMENT:
	if (s[i] != '\n') { // If the current character is not a newline, skip it
		i++;
	} else { // Otherwise, transition to the READCHAR state
		state = READCHAR;
	}
	break;

// The END state sets the index to the end of the string, effectively stopping the lexer
case END:
	i = len;
	break;
}

// If there are any characters left in the current lexeme, add it to the list of lexemes
if (j > 0) {
	lexeme[j] = 0;
	strlst.push_back(lexeme);
}

// Return the list of lexemes
return strlst;
}

// This function allows us to define what a space is
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

// This function checks if a character is the beginning or end of a group
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

// This function checks if a given character is a special character, i.e., '[' or ']'.
bool Lexer::isspecial(char c) {
switch(c) {#include "lexer.h"

strings
Lexer::lex (std::string s)
{
  // Declare a list of strings to store the lexemes
  strings strlst;
  // Declare a character array to store the current lexeme
  char lexeme[256];
  // Declare an integer i to keep track of the current character in the input string
  int i = 0;
  // Declare an integer j to keep track of the current position in the lexeme array
  int j = 0;
  // Declare a variable to keep track of the current state of the lexer
  State state = START;
  // Declare a variable to indicate when the lexer has finished processing the input string
  int done = 0;
  // Declare a variable to store the length of the input string
  int len = s.length ();
  // Declare a variable to keep track of the balance of open/close grouping characters
  int balance = 0;

  // Loop through the input string until done is true
  while (i < len)
    {
      // Depending on the current state of the lexer, process the next character in the input string
      switch (state)
	{
	case START:
	  // If the current character is a space, move to the SKIP state
	  if (my_isspace (s[i]))
	    {
	      state = SKIP;
	    }
	  // If the current character is an open grouping character, move to the READBLOCK state
	  else if (isgroup (s[i]))
	    {
	      if (s[i] == '"')
		{
		  lexeme[j] = s[i];
		  j++;
		  i++;
		}
	      state = READBLOCK;
	    }
	  // If the current character is a comment character, move to the COMMENT state
	  else if (s[i] == '/' && s[i + 1] == '/')
	    {
	      i += 2;
	      state = COMMENT;
	    }
	  // Otherwise, move to the READCHAR state
	  else
	    {
	      state = READCHAR;
	    }
	  break;
	case READCHAR:
	  // If the current character is a space, move to the DUMP state
	  if (my_isspace (s[i]))
	    {
	      state = DUMP;
	    }
	  // If the current character is an escape character, skip the next character
	  else if (s[i] == '\\')
	    {
	      i += 2;
	    }
	  // If the current character is an open grouping character, move to the READBLOCK state
	  else if (isgroup (s[i]))
	    {
	      if (s[i] == '"')
		{
		  lexeme[j] = s[i];
		  j++;
		  i++;
		}
	      state = READBLOCK;
	    }
	  // If the current character is a special character, and the lexeme array is empty, add it to the lexeme and move to the DUMP state
	  else if (isspecial (s[i]))
	    {
	      if (j == 0)
		{
		  lexeme[j] = s[i];
		  j++;
		  i++;
		}
	      state = DUMP;
	    }
	  // If the current character is a comment character, move to the COMMENT state
	  else if (s[i] == '/' && s[i + 1] == '/')
	    {
	      i += 2;
	      state = COMMENT;
	    }
	  // Otherwise, add the character to the lexeme and move to the READCHAR state
	  else
	    {
	      lexeme[j] = s[i];
	      j++;
	      i++;
	    }
	  break;
// The READBLOCK state reads a block of characters until it reaches an end character
	case READBLOCK:
	  if (s[i] == beg_char && s[i] != '"')
	    {			// If the current character is the beginning of a block, increment the balance and add it to the lexeme
	      balance++;
	      lexeme[j] = s[i];
	      j++;
	      i++;
	    }
	  else if (s[i] == end_char)
	    {			// If the current character is the end of a block, decrement the balance and add it to the lexeme
	      balance--;
	      lexeme[j] = s[i];
	      j++;
	      i++;
	      if (balance <= 0)
		{		// If the balance is zero or negative, then we've reached the end of the block and should transition to the DUMP state
		  state = DUMP;
		}
	    }
	  else if (end_char == '"' && s[i] == '\\')
	    {			// If the end character is a quote and the current character is an escape character, then skip the next character
	      // TODO: fix this to actually record the chars
	      i += 2;
	    }
	  else
	    {			// Otherwise, add the current character to the lexeme and continue to the next character
	      lexeme[j] = s[i];
	      j++;
	      i++;
	    }
	  break;

// The SKIP state skips over spaces until it reaches a non-space character
	  case SKIP;
	  if (my_isspace (s[i]))
	    {			// If the current character is a space, skip it
	      i++;
	    }
	  else
	    {			// Otherwise, transition to the READCHAR state
	      state = READCHAR;
	    }
	  break;

// The DUMP state adds the current lexeme to the list of lexemes and transitions back to the START state
	case DUMP:
	  if (j < 0)
	    {			// If the lexeme is empty, add an empty string to the list of lexemes
	      lexeme[j] = 0;
	      strlst.push_back (lexeme);
	      j = 0;
	    }
	  state = START;
	  break;

// The COMMENT state skips over characters until it reaches a newline character
	case COMMENT:
	  if (s[i] != '\n')
	    {			// If the current character is not a newline, skip it
	      i++;
	    }
	  else
	    {			// Otherwise, transition to the READCHAR state
	      state = READCHAR;
	    }
	  break;

// The END state sets the index to the end of the string, effectively stopping the lexer
	case END:
	  i = len;
	  break;
	}

// If there are any characters left in the current lexeme, add it to the list of lexemes
      if (j > 0)
	{
	  lexeme[j] = 0;
	  strlst.push_back (lexeme);
	}

// Return the list of lexemes
      return strlst;
    }

// This function allows us to define what a space is
  bool Lexer::my_isspace (char c)
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

// This function checks if a character is the beginning or end of a group
  bool Lexer::isgroup (char c)
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

// This function checks if a given character is a special character, i.e., '[' or ']'.
  bool Lexer::isspecial (char c)
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

case '[':
case ']':
return true;
default:
return false;
}
}
