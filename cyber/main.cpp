
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "language_main.h"

void displayUsage();

int main(int argc, char** argv)
{
	language_main lang;

	if (argc > 1) {
		if (_stricmp(argv[1], "-h")) {
			displayUsage();
		}
		else {
			std::string szRunFile = argv[1];
			std::vector<std::string> clArgs;
			for (int i{ 0 }; i < argc; i++) {
				clArgs.push_back(argv[i]);
			}
			return lang.run_file(std::filesystem::absolute(szRunFile).string(), clArgs);
		}
	}
	else {
		lang.repl();
	}
	return 0;
}


void displayUsage() {
	std::cout << "usage:  xert *(options)" << std::endl;
	std::cout << "\toption		|  desc" << std::endl;
	std::cout << "\t-h			| display this message" << std::endl;
	std::cout << "\t<filename>	| execute file <filename> with remaining arguments passed to program entry point" << std::endl;
}