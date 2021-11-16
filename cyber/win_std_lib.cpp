#include "win_std_lib.h"


#ifdef BUILD_WINDOWS

#include "FileHandle.hpp"
#include "Utilities.h"
#include "callable.h"
#include "context.h"
#include "ConsoleHandle.hpp"
#include "klass_instance.h"


#include "vo_interface.hpp" // Windows is included here by default
#define DUMMY std::numeric_limits<std::streamsize>::max DUMMY()


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
		throw ExceptionBuilder().Build(ExceptionTypes().RUNTIME(), "could not load dynamic libaray; handle was invalid", Severity().MEDIUM());
	}
	hFunc fn = (hFunc)GetProcAddress(hMod, szFnName.c_str());
	if (!fn) {
		throw ExceptionBuilder().Build(ExceptionTypes().UNRESOLVED_SYMBOL(), "could not locate the function", Severity().MEDIUM());
	}
	return std::make_shared<loaded_native_fn>(szFnName, fn)->setVariadic()->setVariadicAfter(0);
}


std::any win_SetConsoleOpacity(std::shared_ptr<interpreter> i, _args args)
{
	return ConsoleHandle().SetOpacity(args.get<uint8_t>(0));
}

std::any win_SetOutputColor(std::shared_ptr<interpreter> i, _args args)
{
	ConsoleHandle().SetOutputColor(args.get<uint16_t>(0));
	return nullptr;
}

std::any win_ResetOutputColor(std::shared_ptr<interpreter> i, _args args)
{
	ConsoleHandle().ResetOutputColor();
	return nullptr;
}

std::any win_SetCursorPosition(std::shared_ptr<interpreter> i, _args args)
{
	ConsoleHandle().SetCursorPosition(args.get<int16_t>(0), args.get<int16_t>(1));
	return nullptr;
}

std::any win_GetCursorPosition(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<activation_record> coord_ar = std::make_shared<activation_record>();
	coord_ar->szAlias = "Coord";
	coord_ar->environment = std::make_shared<scope<std::any>>();

	COORD coord = ConsoleHandle().GetCursorPosition();

	coord_ar->environment->define("X", static_cast<uint16_t>(coord.X));
	coord_ar->environment->define("Y", static_cast<uint16_t>(coord.Y));

	return klass_instance("Coord", "Coord", coord_ar);
}

std::any win_SetCursorVisibility(std::shared_ptr<interpreter> i, _args args)
{
	ConsoleHandle().SetCursorVisibility(args.get<bool>(0));
	return nullptr;
}

std::any win_GetWindowSize(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<activation_record> coord_ar = std::make_shared<activation_record>();
	coord_ar->szAlias = "Coord";
	coord_ar->environment = std::make_shared<scope<std::any>>();

	COORD coord = ConsoleHandle().GetWindowSize();

	coord_ar->environment->define("X", static_cast<uint16_t>(coord.X));
	coord_ar->environment->define("Y", static_cast<uint16_t>(coord.Y));

	return klass_instance("Coord", "Coord", coord_ar);
}

std::any win_SetTitle(std::shared_ptr<interpreter> i, _args args)
{
	ConsoleHandle().SetTitle(args.get<std::string>(0));
	return nullptr;
}

std::any win_SetWindowSize(std::shared_ptr<interpreter> i, _args args)
{
	ConsoleHandle().SetWindowSize(args.get<int32_t>(0), args.get<int32_t>(1));
	return nullptr;
}


// View

std::any win_view_contructor(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);

	std::shared_ptr<ViewInterface> view = std::make_shared<ViewInterface>(i, Utilities().getCallable(args.at(0)));

	context->define("__raw__",
		view, false, location()
	);
	return nullptr;
}

std::any win_view_contruct(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<ViewInterface> view = context->get<std::shared_ptr<ViewInterface>>("__raw__");

	if (view == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), "__raw__ view was null", Severity().HIGH());
	}

	olc::rcode rc = view->Construct(args.get<int32_t>(0), args.get<int32_t>(1), args.get<int32_t>(2), args.get<int32_t>(3), args.get<bool>(4), args.get<bool>(5), args.get<bool>(6));
	if (rc == olc::rcode::OK) {
		return true;
	}
	return false;
}
std::any win_view_start(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<ViewInterface> view = context->get<std::shared_ptr<ViewInterface>>("__raw__");

	if (view == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), "__raw__ view was null", Severity().HIGH());
	}

	olc::rcode rc = view->Start();
	if (rc == olc::rcode::OK) {
		return true;
	}
	return false;
}

std::any win_view_DrawStringDecal(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<ViewInterface> view = context->get<std::shared_ptr<ViewInterface>>("__raw__");

	if (view == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), "__raw__ view was null", Severity().HIGH());
	}

	olc::vf2d pos(args.get<float>(0), args.get<float>(1));
	olc::vf2d scale(args.get<float>(4), args.get<float>(5));
	olc::Pixel p = args.get<olc::Pixel>(3);
	view->DrawStringDecal(pos, args.get<std::string>(2), p, scale);
	return nullptr;
}

std::any win_view_FillRect(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<ViewInterface> view = context->get<std::shared_ptr<ViewInterface>>("__raw__");

	if (view == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), "__raw__ view was null", Severity().HIGH());
	}

	olc::vf2d pos = args.get<olc::vf2d>(0);
	olc::vf2d size = args.get<olc::vf2d>(1);
	olc::Pixel p = args.get<olc::Pixel>(2);
	view->FillRect(pos, size, p);
	return nullptr;
}

std::any win_view_DrawRect(std::shared_ptr<interpreter> i, _args args)
{
	std::shared_ptr<execution_context> context = Utilities().fetch_context(i);
	std::shared_ptr<ViewInterface> view = context->get<std::shared_ptr<ViewInterface>>("__raw__");

	if (view == nullptr) {
		throw ExceptionBuilder().Build(ExceptionTypes().SYSTEM(), "__raw__ view was null", Severity().HIGH());
	}

	olc::vf2d pos = args.get<olc::vf2d>(0);
	olc::vf2d size = args.get<olc::vf2d>(1);
	olc::Pixel p = args.get<olc::Pixel>(2);
	view->DrawRect(pos, size, p); 
	return nullptr;
}

std::any win_view_vf2d(std::shared_ptr<interpreter> i, _args args)
{
	olc::vf2d v(args.get<float>(0), args.get<float>(1));
	return v;
}

std::any win_view_vi2d(std::shared_ptr<interpreter> i, _args args)
{
	olc::vi2d v(args.get<int32_t>(0), args.get<int32_t>(1));
	return v;
}

std::any win_view_pixel(std::shared_ptr<interpreter> i, _args args)
{
	olc::Pixel p(args.get<uint8_t>(0), args.get<uint8_t>(1), args.get<uint8_t>(2), args.get<uint8_t>(3));
	return p;
}

#endif