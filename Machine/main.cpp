#include "CPU.h"
#include "Compiler.h"
#include "Loader.h"

int main() {
	std::string file_path;

	std::cout << "Enter path to .asm file: ";
	std::cin >> file_path;

	Compiler::compileASM(file_path.c_str());
	Loader::runASM(replace(file_path, ".asm", ".64019").c_str());

	std::cout << "A: " << cpu.A << std::endl;
	std::cout << "X: " << cpu.X << std::endl;
	return 0;
}