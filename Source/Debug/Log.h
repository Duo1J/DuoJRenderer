#pragma once

#include <iostream>

#define Log(...) \
	do { \
		std::cout << "[INFO] " << __VA_ARGS__; \
		std::cout << std::endl; \
	} while (0)

#define LogWarn(...) \
	do { \
		std::cout << "[WARN] " << __VA_ARGS__; \
		std::cout << std::endl; \
	} while (0)

#define LogError(...) \
	do { \
		std::cout << "[ERROR] " << __VA_ARGS__; \
		std::cout << std::endl; \
	} while (0)