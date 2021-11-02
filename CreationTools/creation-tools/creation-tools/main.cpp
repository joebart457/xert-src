

#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdint>



/* dmo c++ https://guidedhacking.com/ 

#include <Windows.h>
#include <iostream>

using namespace std;

class MyHook {
public:
	static MyHook& Instance() {
		static MyHook myHook;
		return myHook;
	}

	HHOOK hook;
	MSLLHOOKSTRUCT mouseStruct;
	void InstallHook();
	void UninstallHook();

	MSG msg;
	int Messsages();
};

LRESULT WINAPI MyMouseCallback(int nCode, WPARAM wParam, LPARAM lParam);

int MyHook::Messsages() {
	while (MyHook::Instance().msg.message != WM_QUIT) {
		if (PeekMessage(&MyHook::Instance().msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&MyHook::Instance().msg);
			DispatchMessage(&MyHook::Instance().msg);
		}
		Sleep(1);
	}
	MyHook::Instance().UninstallHook();
	return (int)MyHook::Instance().msg.wParam;
}

void MyHook::InstallHook() {
	if (!(MyHook::Instance().hook = SetWindowsHookEx(WH_MOUSE_LL, MyMouseCallback, NULL, 0))) {
		MessageBox(NULL, "Could not Install HOOK.", "SetWindowsHookEx", MB_OK | MB_ICONWARNING);
	}
}

void MyHook::UninstallHook() {
	UnhookWindowsHookEx(MyHook::Instance().hook);
}

LRESULT WINAPI MyMouseCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
	if (nCode >= 0) {

		if (pMouseStruct != NULL) {
			cout << "Mouse: x =  " << pMouseStruct->pt.x << "  y =  " << pMouseStruct->pt.y << endl;
		}

		switch (wParam) {

		case WM_LBUTTONUP: {
			printf_s("LEFT CLICK UP\n");
		}break;
		case WM_LBUTTONDOWN: {
			printf_s("LEFT CLICK DOWN\n");
		}break;


		}

	}
	return CallNextHookEx(MyHook::Instance().hook, nCode, wParam, lParam);
}

int main() {
	MyHook::Instance().InstallHook();
	return MyHook::Instance().Messsages();
}
*/


class op {
public:
	op(std::string name, std::string lex)
		:szName{ name }, szLex{ lex }{}

	std::string szName, szLex;
};



void writeDefintionsToFile(const std::string& outFile)
{

	std::vector<std::string> numeric_types = {
	"int8_t",
	"int16_t",
	"int32_t",
	"int64_t",
	"uint8_t",
	"uint16_t",
	"uint32_t",
	"uint64_t",
	"float",
	"double",
	};

	std::vector<op> unary_operators{
		op("not", "!"),
		op("negate", "-"),
	};

	std::vector<op> binary_operators{
		op("add", "+"),
		op("subtract", "-"),
		op("multiply", "*"),
		op("divide", "/"),
		op("lessthan", "<"),
		op("lessthanequal", "<="),
		op("greaterthan", ">"),
		op("greaterthanequal", ">="),
		op("equalequal", "=="),
		op("notequal", "!="),
		op("cast", "::"),
	};

	std::ofstream f(outFile);
	if (f.is_open()) {

		f << "/* Auto-generated */" << std::endl;
		f << "#include \"interpreter.h\"" << std::endl;
		f << "#include \"exceptions.hpp\"" << std::endl;
		f << "#include \"Utilities.h\"\n\n" << std::endl;

		for (auto ty1 : numeric_types) {
			f << "/*\n\n" << ty1 << "\n\n*/" << std::endl;

			for (auto ops : unary_operators) {
				if (ops.szName == "negate" && ty1.size() >= 1 && ty1.at(0) == 'u') {
					// Skip negating unsigned types
				}
				else {
					f << "/*\n\n" << ops.szName << "\n\n*/" << std::endl;

					f << "std::any " << ops.szName << "_" << ty1 << "(std::shared_ptr<interpreter> i, std::any& rhs)" << std::endl;
					f << "{" << std::endl;
					if (ops.szName == "not") {
						f << "\treturn !Utilities().isTruthy(rhs);" << std::endl;
					}
					else if (ops.szName == "negate") {
						f << "\nreturn - std::any_cast<" << ty1 << ">(rhs);" << std::endl;
					}
					f << "}" << std::endl;
				}
			}
		}

		f << "\n\n\n/* Binary Operators*/\n\n\n";




		for (auto ty1 : numeric_types) {
			f << "/*\n\n" << ty1 << "\n\n*/" << std::endl;

			for (auto ops : binary_operators) {
				f << "/*\n\n" << ops.szName << "\n\n*/" << std::endl;
				for (auto ty2 : numeric_types) {
					if (ops.szName == "cast") {
						f << "std::any " << ops.szName << "_" << ty1 << "_" << ty2 << "(std::shared_ptr<interpreter> i, std::any& lhs)" << std::endl;
						f << "{" << std::endl;
						f << "\treturn static_cast<" << ty2 << ">(std::any_cast<" << ty1 << ">(lhs));" << std::endl;
						f << "}" << std::endl;
					}
					else {
						f << "std::any " << ops.szName << "_" << ty1 << "_" << ty2 << "(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs)" << std::endl;
						f << "{" << std::endl;
						if (ops.szName == "divide") {
							f << "\tauto rhsVal = std::any_cast<" << ty2 << ">(rhs);" << std::endl;
							f << "\tif (rhsVal == 0) {" << std::endl;
							f << "\t\tthrow ExceptionBuilder().Build(ExceptionTypes().DIVIDE_BY_ZERO(), \"unable to divide by zero\", Severity().MEDIUM());" << std::endl;
							f << "\t}" << std::endl;
							f << "\treturn std::any_cast<" << ty1 << ">(lhs) / rhsVal;" << std::endl;
						}
						else {
							f << "\treturn std::any_cast<" << ty1 << ">(lhs) " << ops.szLex << " std::any_cast<" << ty2 << ">(rhs);" << std::endl;
						}
						f << "}" << std::endl;
					}
				}	if (ops.szName == "cast") {
					// manually add in casts to string
					f << "std::any " << ops.szName << "_" << ty1 << "_string(std::shared_ptr<interpreter> i, std::any& lhs)" << std::endl;
					f << "{" << std::endl;
					f << "\treturn std::to_string(std::any_cast<" << ty1 << ">(lhs));" << std::endl;
					f << "}" << std::endl;

					// manually add in casts to bool
					f << "std::any " << ops.szName << "_" << ty1 << "_bool(std::shared_ptr<interpreter> i, std::any& lhs)" << std::endl;
					f << "{" << std::endl;
					f << "\treturn Utilities().isTruthy(std::any_cast<" << ty1 << ">(lhs));" << std::endl;
					f << "}" << std::endl;
				}
			}
		}

		f.close();
	}
	else {
		std::cout << "[ERROR] unable to open file " << outFile << std::endl;
	}
}


void writeDeclarationsToFile(const std::string& outFile)
{

	std::vector<std::string> numeric_types = {
	"int8_t",
	"int16_t",
	"int32_t",
	"int64_t",
	"uint8_t",
	"uint16_t",
	"uint32_t",
	"uint64_t",
	"float",
	"double",
	};

	std::vector<op> unary_operators{
		op("not", "!"),
		op("negate", "-"),
	};

	std::vector<op> binary_operators{
		op("add", "+"),
		op("subtract", "-"),
		op("multiply", "*"),
		op("divide", "/"),
		op("lessthan", "<"),
		op("lessthanequal", "<="),
		op("greaterthan", ">"),
		op("greaterthanequal", ">="),
		op("equalequal", "=="),
		op("notequal", "!="),
		op("cast", "::"),
	};

	std::ofstream f(outFile);
	if (f.is_open()) {
		f << "#pragma once\n\n" << std::endl;
		f << "/* Auto-generated */" << std::endl;
		f << "#include <any>" << std::endl;
		f << "#include <memory>" << std::endl;
		f << "#include <cstdint>" << std::endl;
		f << "class interpreter;\n\n" << std::endl;

		for (auto ty1 : numeric_types) {
			f << "/*\n\n" << ty1 << "\n\n*/" << std::endl;

			for (auto ops : unary_operators) {
				if (ops.szName == "negate" && ty1.size() >= 1 && ty1.at(0) == 'u') {
					// Skip negating unsigned types
				}
				else {
					f << "/*\n\n" << ops.szName << "\n\n*/" << std::endl;

					f << "std::any " << ops.szName << "_" << ty1 << "(std::shared_ptr<interpreter> i, std::any& rhs);" << std::endl;
				}
				
			}
		}


		f << "\n\n\n/* Binary Operators*/\n\n\n";




		for (auto ty1 : numeric_types) {
			f << "/*\n\n" << ty1 << "\n\n*/" << std::endl;

			for (auto ops : binary_operators) {
				f << "/*\n\n" << ops.szName << "\n\n*/" << std::endl;
				for (auto ty2 : numeric_types) {
					if (ops.szName == "cast") {
						f << "std::any " << ops.szName << "_" << ty1 << "_" << ty2 << "(std::shared_ptr<interpreter> i, std::any& lhs);" << std::endl;
					}
					else {
						f << "std::any " << ops.szName << "_" << ty1 << "_" << ty2 << "(std::shared_ptr<interpreter> i, std::any& lhs, std::any& rhs);" << std::endl;
					}
				}
				if (ops.szName == "cast") {
					// manually add in casts to string
					f << "std::any " << ops.szName << "_" << ty1 << "_string(std::shared_ptr<interpreter> i, std::any& lhs);" << std::endl;
					// manually add in casts to bool
					f << "std::any " << ops.szName << "_" << ty1 << "_bool(std::shared_ptr<interpreter> i, std::any& lhs);" << std::endl;
				}
			}
		}

		f.close();
	}
	else {
		std::cout << "[ERROR] unable to open file " << outFile << std::endl;
	}
}


void createOperatorRegistration()
{
	std::vector<std::string> numeric_types = {
	"int8_t",
	"int16_t",
	"int32_t",
	"int64_t",
	"uint8_t",
	"uint16_t",
	"uint32_t",
	"uint64_t",
	"float",
	"double",
	};

	std::vector<op> unary_operators{
		op("not", "!"),
		op("negate", "-"),
	};

	std::vector<op> binary_operators{
		op("add", "+"),
		op("subtract", "-"),
		op("multiply", "*"),
		op("divide", "/"),
		op("lessthan", "<"),
		op("lessthanequal", "<="),
		op("greaterthan", ">"),
		op("greaterthanequal", ">="),
		op("equalequal", "=="),
		op("notequal", "!="),
		op("cast", "::"),
	};


	std::cout << "/* START Auto-generation */" << std::endl;


	for (auto ty1 : numeric_types) {
		std::cout << "/*\n\n" << ty1 << "\n\n*/" << std::endl;

		for (auto ops : unary_operators) {
			if (ops.szName == "negate" && ty1.size() >= 1 && ty1.at(0) == 'u') {
				// Skip negating unsigned types
			}
			else {
				std::cout << "/*\n\n" << ops.szName << "\n\n*/" << std::endl;

				std::cout << "opHandler->registerOperator(" << std::endl;
				std::cout << "	std::make_shared<unary_fn>(\"" << ops.szLex << "\", " << ops.szName << "_" << ty1 << ")" << std::endl;
				std::cout << "	->registerParameter(BuildParameter<" << ty1 << ">())" << std::endl;
				std::cout << ");" << std::endl;
			}
		}
	}


	std::cout << "\n\n\n/* Binary Operators*/\n\n\n";




	for (auto ty1 : numeric_types) {
		std::cout << "/*\n\n" << ty1 << "\n\n*/" << std::endl;

		for (auto ops : binary_operators) {
			std::cout << "/*\n\n" << ops.szName << "\n\n*/" << std::endl;
			for (auto ty2 : numeric_types) {
				if (ops.szName == "cast") {
					// manually add in casts since they are technically unary
					std::cout << "opHandler->registerOperator(" << std::endl;
					std::cout << "	std::make_shared<unary_fn>(\"" << ops.szLex << "\", " << ops.szName << "_" << ty1 << "_" << ty2 << ")" << std::endl;
					std::cout << "	->registerParameter(BuildParameter<" << ty1 << ">())" << std::endl;
					std::cout << "   ->returns<" << ty2 << ">()" << "," << std::endl;
					std::cout << "	\"::(\" + std::string(typeid(" << ty1 << ").name()) + \",\" + std::string(typeid(" << ty2 << ").name()) + \")\"" << std::endl;
					std::cout << ");" << std::endl;
				}
				else {
					std::cout << "opHandler->registerOperator(" << std::endl;
					std::cout << "	std::make_shared<binary_fn>(\"" << ops.szLex << "\", " << ops.szName << "_" << ty1 << "_" << ty2 << ")" << std::endl;
					std::cout << "	->registerParameter(BuildParameter<" << ty1 << ">())" << std::endl;
					std::cout << "	->registerParameter(BuildParameter<" << ty2 << ">())" << std::endl;
					std::cout << ");" << std::endl;
				}
				
			}
			if (ops.szName == "cast") {
				// manually add in casts to string
				std::cout << "opHandler->registerOperator(" << std::endl;
				std::cout << "	std::make_shared<unary_fn>(\"" << ops.szLex << "\", " << ops.szName << "_" << ty1 << "_" << "string" << ")" << std::endl;
				std::cout << "	->registerParameter(BuildParameter<" << ty1 << ">())" << std::endl;
				std::cout << "   ->returns<std::string>()" << "," << std::endl;
				std::cout << "	\"::(\" + std::string(typeid(" << ty1 << ").name()) + \",\" + std::string(typeid(std::string).name()) + \")\"" << std::endl;
				std::cout << ");" << std::endl;

				// manually add in casts to bool
				std::cout << "opHandler->registerOperator(" << std::endl;
				std::cout << "	std::make_shared<unary_fn>(\"" << ops.szLex << "\", " << ops.szName << "_" << ty1 << "_" << "bool" << ")" << std::endl;
				std::cout << "	->registerParameter(BuildParameter<" << ty1 << ">())" << std::endl;
				std::cout << "   ->returns<bool>()" << "," << std::endl;
				std::cout << "	\"::(\" + std::string(typeid(" << ty1 << ").name()) + \",\" + std::string(typeid(bool).name()) + \")\"" << std::endl;
				std::cout << ");" << std::endl;
			}
		}
	}

	std::cout << "/* END Auto-generation */" << std::endl;


}

int main(int argc, char** argv)
{
	writeDeclarationsToFile("C:\\zzz_WIP\\xert\\cyber\\numeric_operators.h");
	writeDefintionsToFile("C:\\zzz_WIP\\xert\\cyber\\numeric_operators.cpp");

	createOperatorRegistration();

	return 0;
}
