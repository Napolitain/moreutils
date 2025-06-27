// 🔧 Important: Define UNICODE before including windows.h
#ifndef UNICODE
#define UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <Demoer.hpp>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Demoer demoer;
	demoer.create();
	demoer.run();

	return 0;
}
