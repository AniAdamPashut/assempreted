#ifndef OPCODES_DEFINITION_HPP
#define OPCODES_DEFINITION_HPP

#include <string>
#include <functional>
#include <unordered_map>

#include "state.hpp"

std::string trim(const std::string &str);

void push(State& state, std::string line);

void pop(State& state, std::string line);

void mov(State& state, std::string line);

void add(State& state, std::string line);

void sub(State& state, std::string line);

void inc(State& state, std::string line);

void dec(State& state, std::string line);

void call(State& state, std::string line);

void jmp(State& state, std::string line);

void ret(State& state, std::string line);

void je(State& state, std::string line);

void syscall(State& state, std::string line);

void cmp(State& state, std::string line);

const std::unordered_map<std::string, std::function<void(State& , std::string)>> opcodes = {
    {"push", &push},
    {"pop", &pop},
    {"mov", &mov},
    {"add", &add},
    {"sub", &sub},
    {"inc", &inc},
    {"dec", &dec},
    {"call", &call},
    {"jmp", &jmp},
    {"ret", &ret},
    {"je", &je},
    {"syscall", &syscall},
    {"cmp", &cmp}
};

namespace syscalls {
    void exit_syscall(State &state);

    void write_syscall(State &state);
};

#define SYSCALL_AMOUNT 2

const std::function<void(State &)> syscall_array[] = {
    &syscalls::exit_syscall,
    &syscalls::write_syscall,
};

#endif