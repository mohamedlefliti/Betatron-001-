#include "Betatron.h"
#include <iostream>
#include <string>
#include <vector>

Betatron::Betatron() {
    memory.resize(100, 0);  // Initialize memory with 100 locations, all set to 0
    accumulator = 0;        // Initialize accumulator to 0
    program_counter = 1;    // Start execution at memory location 1
}

void Betatron::read_program() {
    std::string line;
    int address = 1;  // Start storing instructions at memory location 1

    while (std::cin >> line) {
        if (line == "RUN") {
            break;  // Stop reading when "RUN" is encountered
        }

        // Convert the line to an integer and store it in memory
        int instruction = std::stoi(line);
        if (address < 100) {
            memory[address++] = instruction;
        } else {
            std::cerr << "Error: Program too large for memory.\n";
            break;
        }
    }
}

void Betatron::run_program() {
    while (program_counter < 100) {
        int instruction = memory[program_counter];
        if (instruction == 0) break;  // HALT on encountering 0000

        int opcode = instruction / 100;  // First two digits: opcode
        int operand = instruction % 100; // Last two digits: operand

        // Fetch-decode-execute cycle
        switch (opcode) {
            case 10:  // INPUT
                if (operand == 0) {
                    std::cin >> accumulator;
                } else {
                    std::cin >> memory[operand];
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
                memory[operand] = accumulator;
                break;

            case 70:  // JUMP
                program_counter = operand - 1;  // Adjust for increment at end of loop
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

void Betatron::memory_dump() const {
    for (int i = 0; i < 100; ++i) {
        std::cout << "Memory[" << i << "]: " << memory[i] << "\n";
    }
}
