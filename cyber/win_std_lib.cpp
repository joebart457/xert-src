#include "win_std_lib.h"


#ifdef BUILD_WINDOWS

#include "db_framework.h"
#include "ufhndl.h"
#include "Utilities.h"
#include "callable.h"

#include <Windows.h>




// Utilites
std::wstring stringToWString(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}



// Lib

std::any win_lib_constructor(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	HMODULE hMod = LoadLibrary(stringToWString(args.get<std::string>(0)).c_str());
	context->define("hMod", hMod, true, location());

	return nullptr;
}


std::any win_lib_valid(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	HMODULE hMod = context->get<HMODULE>("hMod");
	if (hMod) {
		return true;
	}
	return false;
}

std::any win_lib_get_function(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::string szFnName = args.get<std::string>(0);
	HMODULE hMod = context->get<HMODULE>("hMod");
	if (!hMod) {
		throw PanicException(std::string("could not load dynamic libaray; handle was invalid"), location());
	}
	hFunc fn = (hFunc)GetProcAddress(hMod, szFnName.c_str());
	if (!fn) {
		throw PanicException(std::string("could not locate the function"), location());
	}
	return std::make_shared<loaded_native_fn>(szFnName, fn)->setVariadic()->setVariadicAfter(0);
}

#endif