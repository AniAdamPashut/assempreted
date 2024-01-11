#include "program.hpp"

#include <iostream>
#include <fstream>

#include <string>
#include <array>
#include <cstdint>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <functional> 

#include "opcodes.hpp"

Program::Program() {

}

Program::Program(const char * filename) {
    this->filename = filename;
    this->state = State();
}

void
// parses the file line by line
Program::parse() {
    std::ifstream file(this->filename);

    if (!file.is_open()) {
        throw std::ios_base::failure("Couldn't open file: " + filename);
    }
    std::string line;
    while (std::getline(file, line)) 
    {   
        size_t comma_pos = line.find(';');
        if (comma_pos != std::string::npos) {
            line = line.substr(0, comma_pos);
        }
        
        if (line.ends_with(':')) {
            std::string label = trim(line.substr(0, line.find(':')));
            this->state.label_map[label] = this->state.lines.size();
        }

        this->state.lines.push_back(line);
    }

    while (this->state.pc < this->state.lines.size()) {
        execute(this->state.lines[this->state.pc]);
    } 


    std::cout << "Register values: \n";
    for (auto &pair : this->state.registers) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    file.close();
}

void Program::execute(std::string line) {
    line = trim(line);

    if (line.length() == 0) {
        this->state.pc++;
        return;
    }

    if (line.ends_with(':')) {
        this->state.pc++;
        return;
    }

    std::string opcode = line.substr(0, line.find(' '));
    
    opcodes.at(opcode)(this->state, line);
    
    this->state.pc++;
}

Program::~Program() {
    
}