#define CONIOEX
#include "conioex.h"

#include "ScreenBuffer.h"

#include <iostream>
#include <cstring>

// À‘Ì’è‹`i‚±‚ê‚ª—Bˆê‚Ì bufferj
char buffer[HEIGHT][WIDTH + 1];

void ScreenBuffer_Clear() {
    for (int y = 0; y < HEIGHT; ++y) {
        std::memset(buffer[y], ' ', WIDTH);
        buffer[y][WIDTH] = '\0';
    }
}

void ScreenBuffer_Print(int x, int y, const std::string& text) {
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
    gotoxy(1, 1);

    std::string output;
    output.reserve(WIDTH * HEIGHT + HEIGHT);

    for (int y = 0; y < HEIGHT; ++y) {
        output += buffer[y];
        if (y < HEIGHT - 1) output += "\n";
    }
    std::cout << output;
}