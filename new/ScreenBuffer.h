#pragma once

#include <string>
#include <vector>

struct ScreenBuffer {
    // 作れるサイズ(0..max)
    int width = 0;
    int height = 0;

    wchar_t clearChar = L' ';

    // 最大サイズ(必要なら変更)
    static constexpr int MAX_WIDTH = 80;
    static constexpr int MAX_HEIGHT = 25;
    static constexpr int MAX_CELLS = MAX_WIDTH * MAX_HEIGHT;

    std::vector<wchar_t> cells;
};

// 生成
ScreenBuffer ScreenBuffer_生成(int width, int height, wchar_t clearChar = L' ');

// クリア
void ScreenBuffer_クリア(ScreenBuffer& sb);

// 単文字
void ScreenBuffer_単文字(ScreenBuffer& sb, int x, int y, wchar_t ch);

// 文字列（ワイド）
void ScreenBuffer_文字列W(ScreenBuffer& sb, int x, int y, const wchar_t* s);
void ScreenBuffer_文字列W_OR(ScreenBuffer& sb, int x, int y, const std::wstring& s);

// 文字列（互換：ACP から変換して描画）
void ScreenBuffer_文字列(ScreenBuffer& sb, int x, int y, const char* s);
void ScreenBuffer_文字列OR(ScreenBuffer& sb, int x, int y, const std::string& s);

// 描画（画面(1,1)にまとめて出力）
void ScreenBuffer_出力(const ScreenBuffer& sb);