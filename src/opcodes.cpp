#include "opcodes.hpp"

#include <iostream>

#include "exceptions.hpp"


// Function to trim whitespace from the beginning of a string
std::string ltrim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v"); // Find the first non-whitespace character
    return (start == std::string::npos) ? "" : s.substr(start);
}

// Function to trim whitespace from the end of a string
std::string rtrim(const std::string& s) {
    size_t end = s.find_last_not_of(" \t\n\r\f\v"); // Find the last non-whitespace character
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

// Function to trim whitespace from both ends of a string
std::string trim(const std::string& s) {
    return rtrim(ltrim(s));
}


void push(State &state, std::string line) {
    std::string value = trim(line.substr(line.find(' '), line.length()));

    if (state.registers.contains(value)) {
        state.stk.push(state.registers[value]);
        return;
    }
    
    try {
        int literal = std::stoi(value);
        state.stk.push(literal);
    }
    catch (std::invalid_argument exe) {
        throw parse_error("cannot literal value of:" + value + ":");
    }
}

void pop(State &state, std::string line) {
    size_t first_space = line.find(' ');
    if (first_space == std::string::npos) {
        state.stk.pop();
        return;
    }

    std::string reg = trim(line.substr(first_space, line.length()));

    if (!state.registers.contains(reg)) {
        throw parse_error("Can't pop into " + reg);
    }
    state.registers[reg] = state.stk.top();
    state.stk.pop();
}

void mov(State &state, std::string line) {
    size_t first_space = line.find(' ');
    if (first_space == std::string::npos) {
        throw parse_error("This opcode takes 2 argument as (dest, src)");
    }
    std::string args = trim(line.substr(first_space, line.length()));
    size_t comma = args.find(',');
    if (comma == std::string::npos) {
        throw parse_error("separate them with a comma please");
    }
    std::string first = trim(args.substr(0, comma));
    if (!state.registers.contains(first)) {
        throw parse_error("destination can't be non register");
    }

    std::string second = trim(args.substr(comma + 1, args.length()));

    int value;
    if (!state.registers.contains(second)) {
        try {
            value = std::stoi(second);
        }
        catch (std::invalid_argument err) {
            throw parse_error("Can't recognize the source to move from, prob typo.\n");
        }
        catch (std::out_of_range err) {
            throw parse_error("integer might be bigger than 32-bit");
        }
    }
    else {
        value = state.registers.at(second);
    }

    state.registers[first] = value;
}

void add(State &state, std::string line) {
     size_t first_space = line.find(' ');
    if (first_space == std::string::npos) {
        throw parse_error("This opcode takes 2 argument as (dest, src)");
    }
    std::string args = trim(line.substr(first_space, line.length()));
    size_t comma = args.find(',');
    if (comma == std::string::npos) {
        throw parse_error("separate them with a comma please");
    }
    std::string first = trim(args.substr(0, comma));
    if (!state.registers.contains(first)) {
        throw parse_error("destination can't be non register");
    }

    std::string second = trim(args.substr(comma + 1, args.length()));

    int value;
    if (!state.registers.contains(second)) {
        try {
            value = std::stoi(second);
        }
        catch (std::invalid_argument err) {
            throw parse_error("Can't recognize the source to move from, prob typo.\n");
        }
        catch (std::out_of_range err) {
            throw parse_error("integer might be bigger than 32-bit");
        }
    }
    else {
        value = state.registers.at(second);
    }

    state.registers[first] += value;
}

void sub(State &state, std::string line) {
    size_t first_space = line.find(' ');
    if (first_space == std::string::npos) {
        throw parse_error("This opcode takes 2 argument as (dest, src)");
    }
    std::string args = trim(line.substr(first_space, line.length()));
    size_t comma = args.find(',');
    if (comma == std::string::npos) {
        throw parse_error("separate them with a comma please");
    }
    std::string first = trim(args.substr(0, comma));
    if (!state.registers.contains(first)) {
        throw parse_error("destination can't be non register");
    }

    std::string second = trim(args.substr(comma + 1, args.length()));

    int value;
    if (!state.registers.contains(second)) {
        try {
            value = std::stoi(second);
        }
        catch (std::invalid_argument err) {
            throw parse_error("Can't recognize the source to move from, prob typo.\n");
        }
        catch (std::out_of_range err) {
            throw parse_error("integer might be bigger than 32-bit");
        }
    }
    else {
        value = state.registers.at(second);
    }

    state.registers[first] -= value;
}

void inc(State &state, std::string line) {
    line = trim(line);
    size_t first_space = line.find(' ');
    if (first_space == std::string::npos) {
        return;
    }

    std::string reg = trim(line.substr(first_space, line.length()));
    if (!state.registers.contains(reg)) {
        throw parse_error("Can't increment: " + reg);
    }
    
    state.registers[reg] += 1;
}


void dec(State &state, std::string line) {
    line = trim(line);
    size_t first_space = line.find(' ');
    if (first_space == std::string::npos) {
        return;
    }

    std::string reg = trim(line.substr(first_space, line.length()));

    if (!state.registers.contains(reg)) {
        throw parse_error("Can't decrement: " + reg);
    }
    
    state.registers[reg] -= 1;
}


void call(State &state, std::string line) {
    state.stk.push(state.pc);
    state.call_stack.push(state.stk.size());

    std::string value = trim(line.substr(line.find(' '), line.length()));

    if (state.label_map.contains(value)) {
        state.pc = state.label_map[value];
        return;
    }

    throw parse_error("Can't call non label code");
}

void jmp(State &state, std::string line) {
    std::string value = trim(line.substr(line.find(' '), line.length()));

    if (state.label_map.contains(value)) {
        state.pc = state.label_map[value];
        return;
    }
    
    try {
        int literal = std::stoi(value);
        if (literal > state.lines.size()) {
            throw parse_error("Can't jump forward in time fr");
        }

        if (literal < 0) {
            throw parse_error("Can't jump back in time fr");
        }

        state.pc = literal;
    }
    catch (std::invalid_argument exe) {
        throw parse_error("cannot determine value of:" + value + ":");
    }
}

void ret(State &state, std::string line) {
    if (state.call_stack.size() == 0) {
        return;
    }

    while (state.stk.size() > state.call_stack.top()) {
        state.stk.pop();
    }
    if (state.stk.size() > 0) {
        state.pc = state.stk.top();
        state.stk.pop();
    }
    state.call_stack.pop();
}

void je(State &state, std::string line) {
    std::string value = trim(line.substr(line.find(' '), line.length()));

    if (state.label_map.contains(value)) {
        if (state.flags["EF"]) {
            state.pc = state.label_map[value ];
        }
        return;
    }
    
    try {
        int literal = std::stoi(value);
        if (literal > state.lines.size()) {
            throw parse_error("Can't jump forward in time fr");
        }

        if (literal < 0) {
            throw parse_error("Can't jump back in time fr");
        }
        if (state.flags["EF"]) {
            state.pc = literal;
        }
    }
    catch (std::invalid_argument exe) {
        throw parse_error("cannot determine value of:" + value + ":");
    }
}

void syscall(State &state, std::string line) {
    if (state.registers["ax"] > SYSCALL_AMOUNT) {
        throw parse_error("INVALID SYSCALL NUMBER: " + state.registers["ax"]);
    }
 
    syscall_array[state.registers["ax"]](state);
} 

void cmp(State &state, std::string line) {
    size_t first_space = line.find(' ');
    if (first_space == std::string::npos) {
        throw parse_error("This opcode takes 2 argument as (dest, src)");
    }
    std::string args = trim(line.substr(first_space, line.length()));
    size_t comma = args.find(',');
    if (comma == std::string::npos) {
        throw parse_error("separate them with a comma please");
    }
    std::string first = trim(args.substr(0, comma));
    if (!state.registers.contains(first)) {
        throw parse_error("destination can't be non register");
    }

    std::string second = trim(args.substr(comma + 1, args.length()));

    int value;
    if (!state.registers.contains(second)) {
        try {
            value = std::stoi(second);
        }
        catch (std::invalid_argument err) {
            throw parse_error("Can't recognize the source to move from, prob typo.\n");
        }
        catch (std::out_of_range err) {
            throw parse_error("integer might be bigger than 32-bit");
        }
    }
    else {
        value = state.registers.at(second);
    }

    int diff = state.registers[first] - value;
    state.flags["EF"] = diff == 0;
    state.flags["BF"] = diff > 0;
    state.flags["LF"] = diff < 0;
}

namespace syscalls  
{  
    void exit_syscall(State &state) {
        state.pc = state.lines.size() + 2;
    }

    void write_syscall(State &state) {
        if (state.registers["bx"] > 255) {
            throw parse_error("MAN PLEASE TRY TO INPUT AN ASCII CHAR FR\n");
        }
        std::cout << (char)state.registers["bx"];
    }
} // namespace syscalls 
