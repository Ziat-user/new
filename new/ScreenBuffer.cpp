#define CONIOEX
#include "conioex.h"

#include "ScreenBuffer.h"

#include <cstring>
#include <windows.h>

// 実体定義（これが唯一の buffer）
wchar_t buffer[HEIGHT][WIDTH + 1];

void ScreenBuffer_Clear() {
    for (int y = 0; y < HEIGHT; ++y) {
        std::wmemset(buffer[y], L' ', WIDTH);
        buffer[y][WIDTH] = L'\0';
    }
}

void ScreenBuffer_Print(int x, int y, const std::wstring& text) {
    int px = x - 1;
    int py = y - 1;

    if (py < 0 || py >= HEIGHT) return;
    if (px >= WIDTH) return;
    if (px < 0) px = 0;

    std::size_t start = static_cast<std::size_t>(px);
    for (std::size_t i = 0; i < text.size() && start + i < WIDTH; ++i) {
        buffer[py][start + i] = text[i];
    }
}

void ScreenBuffer_Show() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == nullptr || hOut == INVALID_HANDLE_VALUE) return;

    // スクロールを起こさない：改行を出さず、各行を左端に上書き
    for (int y = 0; y < HEIGHT; ++y) {
        gotoxy(1, y + 1);

        DWORD written = 0;
        WriteConsoleW(hOut, buffer[y], WIDTH, &written, nullptr);
    }

    // カーソルを固定（好み）
    gotoxy(1, 1);
}