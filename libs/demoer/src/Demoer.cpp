#include "Demoer.hpp"
#include <iostream>

// Static instance pointer initialization
Demoer *Demoer::instance_ = nullptr;

Demoer::Demoer() : hwnd_(nullptr) {
    instance_ = this;
}

Demoer::~Demoer() {
    instance_ = nullptr;
}

bool Demoer::create() {
    constexpr wchar_t CLASS_NAME[] = L"DemoerClass";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = Demoer::WndProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClassW(&wc)) {
        MessageBoxW(nullptr, L"RegisterClassW failed", L"Error", MB_OK | MB_ICONERROR);
        return true;
    }

    const HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
        CLASS_NAME,
        L"",
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        nullptr, nullptr, wc.hInstance, nullptr
    );

    if (!hwnd) {
        MessageBoxW(nullptr, L"CreateWindowExW failed", L"Error", MB_OK | MB_ICONERROR);
        return true;
    }

    SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
    ShowWindow(hwnd, SW_SHOW);

    return true;
}

void Demoer::run() {
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

LRESULT Demoer::WndProc(const HWND hwnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            MessageBoxW(nullptr, L"Key down detected", L"Info", MB_OK);
            return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
