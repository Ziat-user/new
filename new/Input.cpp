#define CONIOEX
#include "conioex.h"
#include "Input.h"

int キーボード入力(int キー) {
    // conioex の VirtualKey は 0..255 想定
    static unsigned char prev_state[256] = {};
    const int idx = キー & 0xFF;

    const unsigned char current = static_cast<unsigned char>(inport(キー));
    const int r = (current != 0) && (prev_state[idx] == 0);

    prev_state[idx] = current;
    return r;
}

int マウス入力() {
    static unsigned int prev_state = 0;

    unsigned int current_state = 0;
    if (inport(PM_LEFT))  current_state |= 0b001;
    if (inport(PM_MID))   current_state |= 0b010;
    if (inport(PM_RIGHT)) current_state |= 0b100;

    const unsigned int down = current_state & ~prev_state; // 押した瞬間
    const unsigned int held = current_state;               // 押しっぱなし

    prev_state = current_state;

    // 上位3bit=held、下位3bit=down
    return static_cast<int>((held << 3) | down);
}

int マウス位置取得() {
    int マウスX = inport(PM_CURX) << 8;
    int マウスY = inport(PM_CURY);
    return マウスX + マウスY;
}