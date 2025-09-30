#pragma once

#include <iostream>

#define Log(...) std::cout << "[INFO] " << __VA_ARGS__ << std::endl;

#define LogWarn(...) std::cout << "[WARN] " << __VA_ARGS__ << std::endl;

#define LogError(...) std::cout << "[ERROR] " << __VA_ARGS__ << std::endl;