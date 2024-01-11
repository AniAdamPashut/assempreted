#include <iostream>
#include "program.hpp"

int main(int argc, char **argv) {
    Program p = Program("momo.bass");
    p.parse();
    
    std::cout << "Hello, World\n";
    return 0;
}
