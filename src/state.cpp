#include "state.hpp"


State::State() {
    this->stk = std::stack<int>();
    this->call_stack = std::stack<int>();

    this->registers = {
        {"ax", 0},
        {"bx", 0},
        {"cx", 0},
        {"dx", 0}
    };

    this->flags = {
        {"EF", 0}, // Equal flag
        {"BF", 0}, // Bigger flag
        {"LF", 0}, // Lesser flag
    };

    this->pc = 0;

    this->lines = std::vector<std::string>();
    this->label_map = std::unordered_map<std::string, size_t>();
}

State::~State() {}