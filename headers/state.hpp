#ifndef APPLICATION_STATE_HPP
#define APPLICATION_STATE_HPP

#include <vector>
#include <array>
#include <string>
#include <stack>
#include <cstdint>
#include <unordered_map>


struct State {
    uint32_t pc;

    std::stack<int> stk;
    std::stack<int> call_stack;
    std::unordered_map<std::string, uint32_t> registers;

    std::vector<std::string> lines;
    std::unordered_map<std::string, size_t> label_map;
    std::unordered_map<std::string, bool> flags;
    State();
    ~State();
};


#endif