#ifndef BETATRON_H
#define BETATRON_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // for std::clamp


class Betatron {
private:
    std::vector<int> memory;
    int accumulator;
    int program_counter;

public:
    Betatron();                // Constructor
    void read_program();        // Read the program from input
    void run_program();         // Execute the loaded program
    void memory_dump() const;   // Print the memory contents
};

// Constructor
inline Betatron::Betatron() {
    memory.resize(100, 0);  // Initialize memory with 100 locations, all set to 0
    accumulator = 0;        // Initialize accumulator to 0
    program_counter = 1;    // Start execution at memory location 1
}

// Read program from input until "RUN" is entered
inline void Betatron::read_program() {
    std::string line;
    int address = 1;  // Start storing instructions at memory location 1

    while (std::cin >> line) {
        if (line == "RUN") {
            break;  // Stop reading when "RUN" is encountered
        }

        int instruction = std::stoi(line);
        if (address < 100) {
            memory[address++] = instruction;
        } else {
            std::cerr << "Error: Program too large for memory.\n";
            break;
        }
    }
}

// Execute the loaded program
inline void Betatron::run_program() {
    while (program_counter < 100) {
        int instruction = memory[program_counter];
        if (instruction == 0) break;  // HALT on encountering 0000

        int opcode = instruction / 100;  // First two digits: opcode
        int operand = instruction % 100; // Last two digits: operand

        switch (opcode) {
            case 10:  // INPUT
                if (operand == 0) {
                    std::cin >> accumulator;
                } else {
                    int value;
                    std::cin >> value;
                    memory[operand] = std::clamp(value, 0, 9999);
                }
                break;

            case 20:  // OUTPUT
                if (operand == 0) {
                    std::cout << accumulator << "\n";
                } else {
                    std::cout << memory[operand] << "\n";
                }
                break;

            case 30:  // INC
                accumulator++;
                break;

            case 31:  // DEC
                accumulator--;
                break;

            case 40:  // ADD
                accumulator += memory[operand];
                break;

            case 41:  // SUB
                accumulator -= memory[operand];
                break;

            case 50:  // LOAD
                accumulator = memory[operand];
                break;

            case 60:  // STORE
                memory[operand] = std::clamp(accumulator, 0, 9999);
                break;

            case 70:  // JUMP
                program_counter = operand - 1;  // -1 because we'll increment later
                break;

            case 71:  // JUMPPOS
                if (accumulator > 0) {
                    program_counter = operand - 1;
                }
                break;

            case 72:  // JUMPZERO
                if (accumulator == 0) {
                    program_counter = operand - 1;
                }
                break;

            case 99:  // HALT
                return;

            case 0:  // SKIP
                break;

            default:
                std::cerr << "Error: Unknown opcode " << opcode << "\n";
                return;
        }

        program_counter++;  // Move to the next instruction
    }
}

// Print the current state of memory
inline void Betatron::memory_dump() const {
    for (int i = 0; i < 100; ++i) {
        std::cout << "Memory[" << i << "]: " << memory[i] << "\n";
    }
}

#endif // BETATRON_H
