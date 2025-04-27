#ifndef BETATRON_H
#define BETATRON_H

#include <vector>
#include <string>

class Betatron {
public:
    Betatron();

    void read_program();  // Reads a program from input until "RUN" is entered
    void run_program();   // Executes the loaded program
    void memory_dump() const;  // Prints the current state of memory

private:
    std::vector<int> memory;  // Memory: 100 words (locations)
    int accumulator;          // Accumulator for computations
    int program_counter;      // Tracks the next instruction to execute

    void fetch_decode_execute();  // Implements the fetch-decode-execute cycle
};

#endif
