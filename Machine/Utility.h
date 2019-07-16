#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

static class Utility {
private:
	static std::string abovez(std::string str) {
		return str == "0" ? "" : str;
	}

public:

	static unsigned long stoh(const char* str) {
		std::string s = str;

		return std::stoul(s, nullptr, 16);
	}

	static std::string itoh(std::string s) {
		std::string ret = "";
		std::string hex[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
		for (int i = 0; i <= 255; i++) {
			int div = i / 16;
			if (div == 0) {
				if (std::stoi(s) == std::stoi(hex[i], nullptr, 16)) {
					ret = hex[i];
				}
			} else {
				if (std::stoi(s) == std::stoi(hex[div] + hex[i - (16 * div)], nullptr, 16)) {
					ret = hex[div] + hex[i - (16 * div)];
				}
			}
		}
		return ret;
	}

	static std::string smul(const char* str, int times) {
		std::string s = "";
		for (int i = 0; i < times; i++) {
			s += str;
		}
		return s;
	}

};