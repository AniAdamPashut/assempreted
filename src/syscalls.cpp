#include "syscalls.hpp"

#include <iostream>

#include "exceptions.hpp"

void exit_syscall(State &state) {
    state.pc = state.lines.size() + 2;
}

void write_syscall(State &state) {
    if (state.registers["bx"] > 255) {
        throw parse_error("MAN PLEASE TRY TO INPUT AN ASCII CHAR FR\n");
    }
    std::cout << (char)state.registers["bx"];
}
