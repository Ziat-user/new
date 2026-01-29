#pragma once

struct ScreenBuffer;

// FPS を ScreenBuffer に描画（出力は main 側でまとめて行う）
void showFPS(ScreenBuffer& sb, int x, int y);