#pragma once

#include <string>

struct ScreenBuffer {
    // 使うサイズ（0..max）
    int width = 0;
    int height = 0;

    char clearChar = ' ';

    // 固定最大サイズ（必要なら変更）
    static constexpr int MAX_WIDTH = 80;
    static constexpr int MAX_HEIGHT = 25;
    static constexpr int MAX_CELLS = MAX_WIDTH * MAX_HEIGHT;

    char cells[MAX_CELLS]{};
};

// 生成
ScreenBuffer ScreenBuffer_生成(int width, int height, char clearChar = ' ');

// 操作
void ScreenBuffer_クリア(ScreenBuffer& sb);
void ScreenBuffer_単文字(ScreenBuffer& sb, int x, int y, char ch);
void ScreenBuffer_文字列(ScreenBuffer& sb, int x, int y, const char* s);
void ScreenBuffer_文字列OR(ScreenBuffer& sb, int x, int y, const std::string& s);

// 描画（左上(1,1)にまとめて出力）
void ScreenBuffer_出力(const ScreenBuffer& sb);