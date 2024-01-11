#include <iostream>
#include "program.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Please insert only one filename\n";
        return 1;
    }

    Program p = Program(argv[1]);
    p.parse();
    std::cout << "Hello, World\n";
    return 0;
}
