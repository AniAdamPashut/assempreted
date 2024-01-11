#ifndef APPLICATION_STATE_HPP
#define APPLICATION_STATE_HPP

#include <vector>
#include <array>
#include <string>
#include <stack>
#include <cstdint>
#include <unordered_map>


class State {
public:
    uint32_t pc;

    std::stack<int> stk;
    std::unordered_map<std::string, uint32_t> registers;

    std::vector<std::string> lines;
    std::unordered_map<std::string, size_t> label_map;
    std::unordered_map<std::string, bool> flags;
    State();
    ~State();
};


#endif