#include "Betatron.h"
#include <iostream>

int main() {
    Betatron betatron;

    std::cout << "Welcome to the Betatron-001 Simulator\n";
    std::cout << "Enter your program (one instruction per line, ending with RUN):\n";

    betatron.read_program();  // Read the program from input

    std::cout << "Running program...\n";
    betatron.run_program();   // Execute the program

    std::cout << "Program execution finished.\n";
    std::cout << "Final memory state:\n";
    betatron.memory_dump();   // Display the final state of memory

    return 0;
}
