// This program takes a filename as an argument and reads in binary instructions from the file to execute on a virtual machine.

#include <iostream>  // Header file for input/output stream operations.
#include <fstream>   // Header file for file input/output operations.
#include "stack-vm.h"  // Header file for StackVM class.

using namespace std;

int main(int argc, char *argv[]) {
    // Check if a filename argument was provided.
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl; // Display usage message.
        return 0;  // Exit program.
    }

    // Open the binary file for reading.
    ifstream r(argv[1], ios::binary);

    // Declare variables.
    i32 i;
    vector<i32> prog;

    // Read binary instructions from the file and store them in a vector.
    while (r.read((char*)&i, sizeof(i))) {
        prog.push_back(i);
    }

    // Create a new StackVM object and load the program into it.
    StackVM vm;
    vm.loadProgram(prog);

    // Run the virtual machine.
    vm.run();

    return 0;  // Exit program.
}
