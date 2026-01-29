#define CONIOEX
#include "conioex.h"
#include "Input.h"

int キーボード入力(int キー) {
    static unsigned char prev_state = 0;
    unsigned char current_padbtn_state = inport(キー);
    int r = current_padbtn_state && !prev_state;
    prev_state = current_padbtn_state;
    return r;
}

int マウス入力() {
    static unsigned int prev_state = 0;
    int current_state = 0;
    if (inport(PM_LEFT))   current_state |= 0b001;
    if (inport(PM_MID))    current_state |= 0b010;
    if (inport(PM_RIGHT))  current_state |= 0b100;
    int r = current_state & ~prev_state;
    prev_state = current_state;
    return r;
}

int マウス位置取得() {
    int マウスX = inport(PM_CURX) << 8; //0~80,81個、128,8bit
    int マウスY = inport(PM_CURY);
    
    return マウスX + マウスY;
}