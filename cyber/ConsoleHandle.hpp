#pragma once

#include <vector>
#include <string>
#include <conio.h>
#include <iostream>

#include "Colors.hpp"
#include "BuildDefinitions.hpp"

#ifdef BUILD_WINDOWS
#include <Windows.h>
#endif

class ConsoleHandle {
public:
	ConsoleHandle(){}


	~ConsoleHandle(){}

	static uint8_t ReadKey() {
		return _getch();
	}

	static std::string ReadLine() {
		std::string line{ "" };
		std::getline(std::cin, line);
		return line;
	}

#ifdef BUILD_WINDOWS

	static int32_t SetOpacity(uint8_t alpha) {
		BYTE bAlpha = alpha;
		HWND hWnd = GetConsoleWindow();
		if (hWnd == 0) {
			return -1;
		}
		/* Windows need to be layered to be made transparent. This is done
		* by modifying the extended style bits to contain WS_EX_LAYARED. */
		if (!SetWindowLongPtr(hWnd, GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED)) {
			return -2;
		}

		if (!SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), bAlpha, LWA_ALPHA)) {
			return -3;
		}
		return 0;
	}

	static void SetOutputColor(uint16_t color) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	static void ResetOutputColor() {
		SetOutputColor(LIGHTGRAY | BLACK_B);
	}

	static void SetCursorPosition(int16_t x, int16_t y) {
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD Position;
		Position.X = x;
		Position.Y = y;
		SetConsoleCursorPosition(hOut, Position);
	}

	static COORD GetCursorPosition() {
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO sbInfo;

		GetConsoleScreenBufferInfo(hOut, &sbInfo);

		return sbInfo.dwCursorPosition;
	}

	static void SetCursorVisibility (bool showFlag)
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo(hOut, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(hOut, &cursorInfo);
	}

	static COORD GetWindowSize() {
		// Gets window size in rows and columns
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD coord;
	
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		
		coord.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		coord.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		return coord;
	}

	static void SetTitle(const std::string& name) {
		SetConsoleTitle(std::wstring(name.begin(), name.end()).c_str()); // Only works because name is expected to be 7 bit ascii encoding
	}

	static void SetWindowSize(int32_t width, int32_t height) {
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r); //stores the console's current dimensions

		MoveWindow(console, r.left, r.top, width, height, TRUE); 
	}
#endif

};

