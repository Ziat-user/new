#pragma once

#include <string>

inline constexpr int WIDTH = 80;
inline constexpr int HEIGHT = 25;

// ŽÀ‘Ì‚Í ScreenBuffer.cpp ‚É1‚Â‚¾‚¯’u‚­
extern char buffer[HEIGHT][WIDTH + 1];

void ScreenBuffer_Clear();
void ScreenBuffer_Print(int x, int y, const std::string& text);
void ScreenBuffer_Show();