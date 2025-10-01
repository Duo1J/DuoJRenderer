#pragma once

#include <iostream>

#define Log(msg) \
	do { \
		std::cout << "[INFO] " << msg; \
		std::cout << std::endl; \
	} while (0)

#define LogWarn(msg) \
	do { \
		std::cout << "[WARN] " << msg; \
		std::cout << std::endl; \
	} while (0)

#define LogError(msg) \
	do { \
		std::cout << "[ERROR] " << msg; \
		std::cout << std::endl; \
	} while (0)