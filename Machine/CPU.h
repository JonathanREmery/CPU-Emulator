#pragma once

#include "Utility.h"

class CPU {
private:
	int n = 1;
	int stack_size = 256;

public:
	int A = 0, X = 0;
	int* S;
	int* B;

	CPU() {
		this->B = (int*)malloc(stack_size);
		this->S = B + (stack_size+4);
	}

	~CPU() {
		free(this->B);
	}

	void call(const char* opcode) {
		switch (opcode[n]){

			case 'A':
				(opcode[n + 1] == '0' ? this->A : this->X) = opcode[n - 1] == '0' ? (int)Utility::stoh((std::string(1, opcode[n + 2]) + std::string(1, opcode[n + 3])).c_str()) : opcode[n + 2] == '0' ? this->A : this->X;
				break;

			case 'B':
				(opcode[n + 1] == '0' ? this->A : this->X) += opcode[n - 1] == '0' ? (int)Utility::stoh((std::string(1, opcode[n + 2]) + std::string(1, opcode[n + 3])).c_str()) : opcode[n + 2] == '0' ? this->A : this->X;
				break;

			case 'C':
				(opcode[n + 1] == '0' ? this->A : this->X) -= opcode[n - 1] == '0' ? (int)Utility::stoh((std::string(1, opcode[n + 2]) + std::string(1, opcode[n + 3])).c_str()) : opcode[n + 2] == '0' ? this->A : this->X;
				break;

			case 'D':
				(opcode[n + 1] == '0' ? this->A : this->X) *= opcode[n - 1] == '0' ? (int)Utility::stoh((std::string(1, opcode[n + 2]) + std::string(1, opcode[n + 3])).c_str()) :opcode[n + 2] == '0' ? this->A : this->X;
				break;

			case 'E':
				this->S -= (this->S - 0x4 >= this->B) ? 0x4 : 0x0;
				*this->S = opcode[n-1]=='0'?(int)Utility::stoh((std::string(1, opcode[n + 2]) + std::string(1, opcode[n + 3])).c_str()):opcode[n+1]=='0'?this->A:this->X;
				break;
			
			case 'F':
				opcode[n - 1] == '1' ? (opcode[n + 1] == '0' ? this->A : this->X) = *this->S:NULL;
				*this->S = 0x0;
				this->S += ((this->S + 4) - this->B <= stack_size) ? 0x4 : 0x0;
				break;
		}
	}
};

CPU cpu;