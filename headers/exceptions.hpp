#ifndef CUSTOM_EXCEPTIONS_HPP
#define CUSTOM_EXCEPTIONS_HPP

#include <stdexcept>

class parse_error : public std::runtime_error {
public:
    parse_error(const std::string &message) 
        : std::runtime_error(message) {}
};


#endif