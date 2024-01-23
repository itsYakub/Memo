#pragma once

#include <string>

class Debug {
public:
    static void Log(const std::string text);
    static void Warn(const std::string text);
    static void Err(const std::string text);
};