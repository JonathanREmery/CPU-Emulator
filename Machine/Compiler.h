#pragma once

#include "Utility.h"
#include "Parse.h"

static class Compiler {
public:

	static void compileASM(const char* filename) {
		using namespace std;

		ifstream input_file;
		string line;
		std::string read;
		vector<std::string> lines;
		std::string compiled;

		input_file.open(filename, ios::in);
		if (input_file.is_open()) {
			while (getline(input_file, line)) {
				read += line + "\n";
			}
			lines = split(read, "\n");
			lines.pop_back();
			input_file.close();
		} else {
			printf("Could not open file!\n");
			input_file.close();
		}
		if (lines.size() > 0) {
			ofstream compiled;
			compiled.open(replace(filename, ".asm", ".64019"));
			for (int i = 0; i < lines.size(); i++) {
				std::string instruction = "";
				std::string r1 = "";
				std::string r2 = "";
				std::string val = "";
				std::string instruction_m = "";
				std::string r1_m = "";
				std::string r2_m = "";
				std::string val_m = "";
				 
				std::string line_m = "";
				instruction = (count(lines[i], "POP") == 0 ? split(lines[i], " ")[0] : count(lines[i], "POPR") == 0 ? "POP" : split(lines[i], " ")[0]);
				if (instruction == "MOVR" || instruction == "ADDR" || instruction == "SUBR" || instruction == "MULR") {
					r1 = split(split(lines[i], ",")[0], " ")[1];
					r2 = split(lines[i], ", ")[1];
				} else if (instruction == "PUSHR" || instruction == "POPR") {
					r1 = split(lines[i], " ")[1];
				} else if (instruction == "PUSH") {
					val = split(lines[i], " ")[1];
				} else if (instruction == "MOV" || instruction == "ADD" || instruction == "SUB" || instruction == "MUL") {
					r1 = split(split(lines[i], ",")[0], " ")[1];
					val = split(lines[i], " ")[2];
				}
				instruction_m = instruction=="MOV"?"0A":instruction=="ADD"?"0B":instruction=="SUB"?"0C":instruction=="MUL"?"0D":instruction=="PUSH"?"0E":instruction=="POP"?"0F":instruction=="MOVR"?"1A":instruction=="ADDR"?"1B":instruction=="SUBR"?"1C":instruction=="MULR"?"1D":instruction=="PUSHR"?"1E":instruction=="POPR"?"1F":"00";
				line_m += instruction_m;
				if (!r1.empty()) {
					r1_m = r1 == "A" ? "0" : "1";
					line_m += r1_m;
				}
				if (!r2.empty()) {
					r2_m = r2 == "A" ? "0" : "1";
					line_m += r2_m + "0";
				}
				if (!val.empty()) {
					val_m = Utility::itoh(val);
					line_m += Utility::smul("0", 2 - val_m.size()) + val_m;
				}
				if (!r1.empty() && val.empty() && r2.empty()) {
					line_m += "00";
				}
				compiled.write(line_m.c_str(), 5);
				if (i != lines.size() - 1) {
					compiled.write(" ", 1);
				}
			}
			compiled.close();
		}
	}
};