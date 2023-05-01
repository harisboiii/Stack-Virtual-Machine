# This line sets the variable "CFLAGS" to "-std=c++11"
CFLAGS=-std=c++11

# This line defines the "all" target, which depends on the "sasm" target
all: sasm 

# This line defines the "sasm" target, which depends on the "sasm.o" and "lexer.o" targets
# It compiles "sasm.o" and "lexer.o" into an executable file called "sasm"
sasm: sasm.o lexer.o
	$(CXX) $(CFLAGS) sasm.o lexer.o -o $@

# This line defines the "lexer.o" target, which depends on the "lexer.h" and "lexer.cpp" files
# It compiles "lexer.cpp" into an object file called "lexer.o"
lexer.o: lexer.h lexer.cpp
	$(CXX) $(CFLAGS) -c lexer.cpp

# This line defines the "sasm.o" target, which depends on the "lexer.h" and "sasm.cpp" files
# It compiles "sasm.cpp" into an object file called "sasm.o"
sasm.o: lexer.h sasm.cpp
	$(CXX) $(CFLAGS) -c sasm.cpp

# This line defines the "clean" target, which removes the "sasm" executable and any object files or binary files
clean:
	rm -f sasm *.o *.bin
