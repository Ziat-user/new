#define CONIOEX
#include "conioex.h"

#include "ScreenBuffer.h"

#include <algorithm>
#include <string>
#include <windows.h>

namespace {
    // (x,y) の2次元座標を cells の1次元インデックスに変換する
    // NOTE: 範囲チェックは呼び出し側で行う
    int Index(const ScreenBuffer& sb, int x, int y) noexcept {
        return y * sb.width + x;
    }

    int ClampSize(int v, int maxv) noexcept {
        if (v < 0) return 0;
        if (v > maxv) return maxv;
        return v;
    }

    std::wstring ToWideFromACP(const char* s) {
        if (!s) return {};
        const int srcLen = static_cast<int>(::strlen(s));
        if (srcLen <= 0) return {};

        const int wlen = ::MultiByteToWideChar(CP_ACP, 0, s, srcLen, nullptr, 0);
        if (wlen <= 0) return {};

        std::wstring ws;
        ws.resize(static_cast<size_t>(wlen));
        ::MultiByteToWideChar(CP_ACP, 0, s, srcLen, ws.data(), wlen);
        return ws;
    }
}

ScreenBuffer ScreenBuffer_生成(int width, int height, wchar_t clearChar) {
    ScreenBuffer sb{};
    sb.width = ClampSize(width, ScreenBuffer::MAX_WIDTH);
    sb.height = ClampSize(height, ScreenBuffer::MAX_HEIGHT);
    sb.clearChar = clearChar;

    sb.cells.assign(static_cast<size_t>(sb.width) * static_cast<size_t>(sb.height), sb.clearChar);
    return sb;
}

void ScreenBuffer_クリア(ScreenBuffer& sb) {
    std::fill(sb.cells.begin(), sb.cells.end(), sb.clearChar);
}

void ScreenBuffer_単文字(ScreenBuffer& sb, int x, int y, wchar_t ch) {
    if (x < 0 || y < 0 || x >= sb.width || y >= sb.height) return;
    sb.cells[static_cast<size_t>(Index(sb, x, y))] = ch;
}

void ScreenBuffer_文字列W(ScreenBuffer& sb, int x, int y, const wchar_t* s) {
    if (!s) return;
    if (y < 0 || y >= sb.height) return;

    int px = x;
    for (const wchar_t* p = s; *p; ++p) {
        if (px >= 0 && px < sb.width) {
            ScreenBuffer_単文字(sb, px, y, *p);
        }
        ++px;
        if (px >= sb.width) break;
    }
}

void ScreenBuffer_文字列W_OR(ScreenBuffer& sb, int x, int y, const std::wstring& s) {
    ScreenBuffer_文字列W(sb, x, y, s.c_str());
}

void ScreenBuffer_文字列(ScreenBuffer& sb, int x, int y, const char* s) {
    const std::wstring ws = ToWideFromACP(s);
    ScreenBuffer_文字列W(sb, x, y, ws.c_str());
}

void ScreenBuffer_文字列OR(ScreenBuffer& sb, int x, int y, const std::string& s) {
    ScreenBuffer_文字列(sb, x, y, s.c_str());
}

void ScreenBuffer_出力(const ScreenBuffer& sb) {
    gotoxy(1, 1);

    std::wstring out;
    out.reserve(static_cast<size_t>(sb.width + 1) * static_cast<size_t>(sb.height));

    for (int y = 0; y < sb.height; ++y) {
        const wchar_t* row = &sb.cells[static_cast<size_t>(y) * static_cast<size_t>(sb.width)];
        out.append(row, row + sb.width);
        if (y != sb.height - 1) out.push_back(L'\n');
    }

    HANDLE hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD written = 0;
    ::WriteConsoleW(hOut, out.c_str(), static_cast<DWORD>(out.size()), &written, nullptr);
}