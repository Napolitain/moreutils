#pragma once

// 🔧 Important: Define UNICODE before including windows.h
#ifndef UNICODE
#define UNICODE
#define _UNICODE
#endif

#include <windows.h>

class Demoer {
	HINSTANCE hInstance_;
	HWND hwnd_;
	static Demoer *instance_;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	Demoer();

	~Demoer();

	bool create();

	static void run();
};
