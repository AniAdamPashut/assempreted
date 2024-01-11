#ifndef SYSCALL_LIST_HPP
#define SYSCALL_LIST_HPP

#include <array>
#include <cstdint>
#include <functional>

#include "state.hpp"

#define SYSCALL_AMOUNT 2

void exit_syscall(State &state);

void write_syscall(State &state);

std::array<std::function<void(State &)>, SYSCALL_AMOUNT> syscall_array = {
    &exit_syscall,
    &write_syscall,
};

#endif