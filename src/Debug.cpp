#include "Debug.hpp"

#include <string>
#include <iostream>

void Debug::Log(const std::string text) {
    std::cout << "[LOG] " << text << std::endl;
}

void Debug::Warn(const std::string text) {
    std::cout << "[WARN] " << text << std::endl;
}

void Debug::Err(const std::string text) {
    std::cout << "[ERR] " << text << std::endl;
}
