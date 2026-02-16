#pragma once

#include <string>
struct ScreenBuffer;

// ─────────────────────────────────────────────
// UIInput : 1フレーム分のUI入力（Scene側で埋めて渡す）
// ─────────────────────────────────────────────
struct UIInput {
    int mouseX = 0;         // マウスX座標 (0-based)
    int mouseY = 0;         // マウスY座標 (0-based)
    bool mouseDownL = false; // 左ボタン押下（押した瞬間）
    bool mouseHeldL = false; // 左ボタン押下中（押し続けている）
};

// ─────────────────────────────────────────────
// UIButton : 矩形ボタンの定義
//   x, y : 左上座標 (0-based)
//   w, h : 幅・高さ（文字単位）
//   label: ボタン中央に表示するラベル（日本語OK）
// ─────────────────────────────────────────────
struct UIButton {
    int x = 0; // 左上X座標 (0-based)
    int y = 0; // 左上Y座標 (0-based)
    int w = 0; // 幅（文字数）
    int h = 0; // 高さ（行数）
    std::wstring label; // ボタン中央ラベル（日本語OK）
};

// ボタンを ScreenBuffer に描画する（ホバー時はハイライト表示）
void UI_DrawButton(const UIButton& b, const UIInput& in);

// ボタンがクリックされたか判定する（マウス左ボタン down かつ矩形内）
bool UI_ButtonClicked(const UIButton& b, const UIInput& in);