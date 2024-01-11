#ifndef PROGRAM_CLASS_HPP
#define PROGRAM_CLASS_HPP

#include <string>

#include "state.hpp"

class Program {
public:
    std::string filename;
    
    Program();
    Program(std::string filename);
    ~Program();
    void parse();

private:
    State state;
    void execute(std::string line);
};


#endif