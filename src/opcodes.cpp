#include "opcodes.hpp"
#include "exceptions.hpp"

#include <iostream>


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
        throw parse_error("cannot determine value of:" + value + ":");
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
        throw parse_error("Hey yo didn't I ask you to specify args with mov mnemonic?");
    }
    std::string args = trim(line.substr(first_space, line.length()));
    size_t comma = args.find(',');
    if (comma == std::string::npos) {
        throw parse_error("I ALSO REQUIRED YOU TO PLACE A COMMA BETWEEN THEM DIDN'T I????");
    }
    std::string first = trim(args.substr(0, comma));
    if (!state.registers.contains(first)) {
        throw parse_error("MAN DONT TRY TO MOV INTO A NON REGISTER WTF IS WRONG WITH YOU??");
    }

    std::string second = trim(args.substr(comma + 1, args.length()));

    int value;
    if (!state.registers.contains(second)) {
        try {
            value = std::stoi(second);
        }
        catch (std::invalid_argument err) {
            throw parse_error("MAN JUST TRY TO MOV A REGISTER OR A LITERAL NOT JUST WEIRD SHIT\n");
        }
        catch (std::out_of_range err) {
            throw parse_error("PLEASE ENTER A FUCKING 32-BIT INTEGER");
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
        throw parse_error("Hey yo didn't I ask you to specify args with mov mnemonic?");
    }
    std::string args = trim(line.substr(first_space, line.length()));
    size_t comma = args.find(',');
    if (comma == std::string::npos) {
        throw parse_error("I ALSO REQUIRED YOU TO PLACE A COMMA BETWEEN THEM DIDN'T I????");
    }
    std::string first = trim(args.substr(0, comma));
    if (!state.registers.contains(first)) {
        throw parse_error("MAN DONT TRY TO MOV INTO A NON REGISTER WTF IS WRONG WITH YOU??");
    }

    std::string second = trim(args.substr(comma + 1, args.length()));

    int value;
    if (!state.registers.contains(second)) {
        try {
            value = std::stoi(second);
        }
        catch (std::invalid_argument err) {
            throw parse_error("MAN JUST TRY TO MOV A REGISTER OR A LITERAL NOT JUST WEIRD SHIT\n");
        }
        catch (std::out_of_range err) {
            throw parse_error("PLEASE ENTER A FUCKING 32-BIT INTEGER");
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
        throw parse_error("Hey yo didn't I ask you to specify args with mov mnemonic?");
    }
    std::string args = trim(line.substr(first_space, line.length()));
    size_t comma = args.find(',');
    if (comma == std::string::npos) {
        throw parse_error("I ALSO REQUIRED YOU TO PLACE A COMMA BETWEEN THEM DIDN'T I????");
    }
    std::string first = trim(args.substr(0, comma));
    if (!state.registers.contains(first)) {
        throw parse_error("MAN DONT TRY TO MOV INTO A NON REGISTER WTF IS WRONG WITH YOU??");
    }

    std::string second = trim(args.substr(comma + 1, args.length()));

    int value;
    if (!state.registers.contains(second)) {
        try {
            value = std::stoi(second);
        }
        catch (std::invalid_argument err) {
            throw parse_error("MAN JUST TRY TO MOV A REGISTER OR A LITERAL NOT JUST WEIRD SHIT\n");
        }
        catch (std::out_of_range err) {
            throw parse_error("PLEASE ENTER A FUCKING 32-BIT INTEGER");
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

void ret(State &state, std::string line) {}

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

void syscall(State &state, std::string line) {} 

void cmp(State &state, std::string line) {
    size_t first_space = line.find(' ');
    if (first_space == std::string::npos) {
        throw parse_error("Hey yo didn't I ask you to specify args with cmp mnemonic?");
    }

    std::string args = trim(line.substr(first_space, line.length()));
    size_t comma = args.find(',');
    if (comma == std::string::npos) {
        throw parse_error("I ALSO REQUIRED YOU TO PLACE A COMMA BETWEEN THEM DIDN'T I????");
    }
    std::string first = trim(args.substr(0, comma));
    if (!state.registers.contains(first)) {
        throw parse_error("MAN DONT TRY TO MOV INTO A NON REGISTER WTF IS WRONG WITH YOU??");
    }

    std::string second = trim(args.substr(comma + 1, args.length()));
    int value;
    if (!state.registers.contains(second)) {
        try {
            value = std::stoi(second);
        }
        catch (std::invalid_argument err) {
            throw parse_error("MAN JUST TRY TO MOV A REGISTER OR A LITERAL NOT JUST WEIRD SHIT\n");
        }
        catch (std::out_of_range err) {
            throw parse_error("PLEASE ENTER A FUCKING 32-BIT INTEGER");
        }
    }
    else {
        value = state.registers.at(second);
    }

    int diff = state.registers[first] - value;
    state.flags["EF"] = diff == 0;
    state.flags["BF"] = diff > 0;
    state.flags["LF"] = diff < 0;

    std::cout << "EF is " << state.flags["EF"] << "\n";
}