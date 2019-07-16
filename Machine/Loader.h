#pragma once

#include "CPU.h"
#include "Parse.h"

static class Loader {
public:

	static void runASM(const char* filename) {
		using namespace std;

		ifstream input_file;
		string line;
		vector<std::string> read;

		input_file.open(filename, ios::in);
		if (input_file.is_open()) {
			getline(input_file, line);
			if (line != "") {
				read = split(line, " ");
			}
			input_file.close();
		} else {
			printf("Could not open file!\n");
			input_file.close();
		}

		if (read.size() != 0) {
			for (int i = 0; i < read.size(); i++) {
				cpu.call(read[i].c_str());
			}
		}
	}
};