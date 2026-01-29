#define CONIOEX
#include "conioex.h"

#include "ScreenBuffer.h"

#include <algorithm>
#include <iostream>
#include <string>

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
}

ScreenBuffer ScreenBuffer_生成(int width, int height, char clearChar) {
    ScreenBuffer sb{};
    sb.width = ClampSize(width, ScreenBuffer::MAX_WIDTH);
    sb.height = ClampSize(height, ScreenBuffer::MAX_HEIGHT);
    sb.clearChar = clearChar;

    ScreenBuffer_クリア(sb);
    return sb;
}

void ScreenBuffer_クリア(ScreenBuffer& sb) {
    const int count = sb.width * sb.height;
    std::fill_n(sb.cells, count, sb.clearChar);
}

void ScreenBuffer_単文字(ScreenBuffer& sb, int x, int y, char ch) {
    if (x < 0 || y < 0 || x >= sb.width || y >= sb.height) return;
    sb.cells[static_cast<size_t>(Index(sb, x, y))] = ch;
}

void ScreenBuffer_文字列(ScreenBuffer& sb, int x, int y, const char* s) {
    if (!s) return;
    if (y < 0 || y >= sb.height) return;

    int px = x;
    for (const char* p = s; *p; ++p) {
        if (px >= 0 && px < sb.width)
            ScreenBuffer_単文字(sb, px, y, *p);
        ++px;
        if (px >= sb.width) break;
    }
}

void ScreenBuffer_文字列OR(ScreenBuffer& sb, int x, int y, const std::string& s) {
    ScreenBuffer_文字列(sb, x, y, s.c_str());
}

void ScreenBuffer_出力(const ScreenBuffer& sb) {
    gotoxy(1, 1);

    std::string out;
    out.reserve(static_cast<size_t>(sb.width + 1) * static_cast<size_t>(sb.height));

    for (int y = 0; y < sb.height; ++y) {
        const char* row = &sb.cells[static_cast<size_t>(y) * static_cast<size_t>(sb.width)];
        out.append(row, row + sb.width);
        if (y != sb.height - 1) out.push_back('\n');
    }

    std::cout << out;
    std::cout.flush();
}