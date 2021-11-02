#pragma once

#ifndef __INCLUDE_KEYWORDS_H
#define __INCLUDE_KEYWORDS_H

#include <string>

class Keywords {
public:
	static std::string FUNCTION() { return "function"; }
	static std::string CLASS() { return "class"; }
	static std::string SWITCH() { return "switch"; }
	static std::string CASE() { return "case"; }
	static std::string DEFAULT() { return "default"; }

	static std::string RUN() { return "run"; }
	static std::string RECOVER() { return "recover"; }
	static std::string ON() { return "on"; }
	static std::string PANIC() { return "panic"; }
	static std::string TRY() { return "try"; }
	static std::string CATCH() { return "catch"; }

	// Types

	static std::string NUL() { return "nul"; }
	static std::string CHAR() { return "char"; }
	static std::string BOOL() { return "bool"; }
	static std::string STRING() { return "string"; }
	static std::string UINT8_T() { return "uint8_t"; }
	static std::string UINT16_T() { return "uint16_t"; }
	static std::string UINT32_T() { return "uint32_t"; }
	static std::string UINT64_T() { return "uint64_t"; }
	static std::string INT8_T() { return "int8_t"; }
	static std::string INT16_T() { return "int16_t"; }
	static std::string INT32_T() { return "int32_t"; }
	static std::string INT64_T() { return "int64_t"; }
	static std::string FLOAT_T() { return "float_t"; }
	static std::string DBLFLOAT_T() { return "dblfloat_t"; }
	static std::string ANY_T() { return "any_t"; }
	static std::string NULLPTR_T() { return "nullptr_t"; }



	static std::string DIRECTIVE() { return "directive"; }
	static std::string INJECT() { return "inject"; }
	static std::string EXTENSION() { return "extension"; }

	static std::string IF() { return "if"; }
	static std::string ELSE() { return "else"; }
	static std::string WHILE() { return "while"; }
	static std::string RETURN() { return "return"; }
	static std::string BREAK() { return "break"; }
	static std::string CONTINUE() { return "continue"; }

	static std::string LCURLY() { return "lcurly"; }
	static std::string RCURLY() { return "rcurly"; }
	static std::string LPAREN() { return "lparen"; }
	static std::string RPAREN() { return "rparen"; }
	static std::string LBRACKET() { return "lbracket"; }
	static std::string RBRACKET() { return "rbrakcet"; }
	static std::string LCARAT() { return "lcarat"; }
	static std::string RCARAT() { return "rcarat"; }

	static std::string COMMA() { return "comma"; }
	static std::string DOT() { return "dot"; }
	static std::string SEMI() { return "semi"; }
	static std::string COLON() { return "colon"; }
	static std::string BANG() { return "bang"; }

	static std::string EQUAL() { return "equal"; }
	static std::string EQUALEQUAL() { return "equalequal"; }
	static std::string BANGEQUAL() { return "bangequal"; }
	static std::string LESSTHAN() { return "lessthan"; }
	static std::string LESSTHANEQUAL() { return "lessthanequal"; }
	static std::string GREATERTHAN() { return "greaterthan"; }
	static std::string GREATERTHANEQUAL() { return "greaterthanequal"; }

	static std::string ADD() { return "add"; }
	static std::string SUBTRACT() { return "subtract"; }
	static std::string ASTERISK() { return "asterisk"; }
	static std::string FORWARDSLASH() { return "forwardslash"; }
	static std::string BACKSLASH() { return "backslash"; }
	static std::string UPCARAT() { return "upcarat"; }

	static std::string AND() { return "and"; }
	static std::string OR() { return "or"; }

	static std::string TYPEOF() { return "typeof"; }
	static std::string CAST() { return "cast"; }

	static std::string BOOLFALSE() { return "false"; }
	static std::string BOOLTRUE() { return "true"; }
	static std::string NEW() { return "new"; }

};

#endif