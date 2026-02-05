#pragma once

#include <string>

struct ScreenBuffer;

// 1フレーム分のUI入力（Scene側で埋めて渡す）
struct UIInput {
    int mouseX = 0;      // 0-based
    int mouseY = 0;      // 0-based
    bool mouseDownL = false; // 左ボタン押下（down）
    bool mouseHeldL = false; // 左ボタン押下中（held）
};

struct UIButton {
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    std::wstring label;
};

// ボタン描画（hover/pressedで見た目を変える）
void UI_DrawButton(const UIButton& b, const UIInput& in);

// ボタンが「クリックされた」フレームなら true
bool UI_ButtonClicked(const UIButton& b, const UIInput& in);