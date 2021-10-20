#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ContextBuilder.hpp"
#include "FileHandle.hpp"


class language_main {
public:
	language_main() {}
	~language_main() {}

	int run_file(const std::string& szFilePath, std::shared_ptr<_clArgs> args)
	{
		try {
			auto interp = ContextBuilder().BuildInterpreter(FileHandle().parent_path(szFilePath), args, m_bLightweight);
			interp->interpret(FileHandle().readFileAsString(szFilePath));
			return 0;
		}
		catch (PanicException pe) {
			std::cout << pe.fullTrace();
			return -1;
		}
		catch (ProgramException pe) {
			std::cout << pe.fullTrace();
			return -1;
		}
		catch (std::exception e) {
			std::cout << e.what();
			return -999;
		}
	}


	void repl() {
		bool bFinished = false;
		bool bShowTokens = false;
		std::string szText;
		auto i = ContextBuilder().BuildInterpreter(m_bLightweight);
		auto p = ContextBuilder().BuildParser();
		auto t = ContextBuilder().BuildTokenizer();
		while (!bFinished) {
			std::cout << (szText == "" ? "" : "\n") << ">$ ";
			std::getline(std::cin, szText);
			if (szText == "-debug:show-tokens") {
				bShowTokens = !bShowTokens;
				std::cout << "show-tokens = " << std::boolalpha << bShowTokens;
				continue;
			}
			if (szText == "-debug:reset") {
				bShowTokens = false;
				std::cout << "show-tokens = " << std::boolalpha << bShowTokens;
				continue;
			}
			if (szText == "-debug") {
				std::cout << "show-tokens = " << std::boolalpha << bShowTokens;
				continue;
			}
			if (szText == "-e") {
				auto c = Utilities().fetch_context(i);
				c->output();
				continue;
			}
			if (szText == "exit") {
				break;
			}
			try {
				i->interpret(p->parse(t->tokenize(szText, bShowTokens)));
			}
			catch (PanicException pe) {
				std::cout << pe.fullTrace();
			}
			catch (ProgramException pe) {
				std::cout << pe.fullTrace();
			}
			catch (std::exception e) {
				std::cout << e.what();
			}
		}

	}

	void UseLightweight()
	{
		m_bLightweight = true;
	}

private:
	bool m_bLightweight{ false };
};