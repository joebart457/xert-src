
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "language_main.h"
#include "clArgs.hpp"


void displayUsage();

int main(int argc, char** argv)
{
	language_main lang;

	_clArgs args;
	args.RegisterBooleanOption("--xhelp", "-xh", -1, false)
		.RegisterBooleanOption("--xlightweight", "-xl", -1, false)
		.RegisterStringOption("--xrunfile", "-xr", 1, "");
	
	std::shared_ptr<_clArgs> usrArgs = args.Fill(argc, argv);

	if (args.TryGetBooleanOption("--xhelp", false, true)) {
		displayUsage();
	}

	if (args.TryGetBooleanOption("--xlightweight", false, true)) {
		lang.UseLightweight();
	}

	if (!args.TryGetStringOption("--xrunfile", "", true).empty()) {
		std::string szRunFile = args.TryGetStringOption("--xrunfile", "", true);
		
		return lang.run_file(std::filesystem::absolute(szRunFile).string(), usrArgs);
	}
	else {
		displayUsage();
		lang.repl();
		return 0;
	}
	return 0;
}


void displayUsage() {
	std::cout << "usage:  xert *(options)" << std::endl;
	std::cout << "\toption                      | description" << std::endl;
	std::cout << "\t-xh (--xhelp)               | display this message" << std::endl;
	std::cout << "\t-xr (--xrunfile) <filename> | execute file <filename> with remaining arguments passed to program entry point" << std::endl;
	std::cout << "\t-xl (--xlightweight)        | load only essential library functions" << std::endl;

}