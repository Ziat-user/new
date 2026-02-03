#include "UI.h"
#include "ScreenBuffer.h"

#include <algorithm>
#include <string>

namespace {
    bool HitTest(const UIButton& b, int px, int py) noexcept {
        if (b.w <= 0 || b.h <= 0) return false;
        return (px >= b.x) && (py >= b.y) && (px < b.x + b.w) && (py < b.y + b.h);
    }

    void DrawHLine(ScreenBuffer& sb, int x, int y, int w, char ch) {
        for (int i = 0; i < w; ++i) ScreenBuffer_単文字(sb, x + i, y, ch);
    }

    void DrawVLine(ScreenBuffer& sb, int x, int y, int h, char ch) {
        for (int i = 0; i < h; ++i) ScreenBuffer_単文字(sb, x, y + i, ch);
    }

    void DrawFrame(ScreenBuffer& sb, const UIButton& b, char tl, char tr, char bl, char br, char h, char v) {
        if (b.w < 2 || b.h < 2) return;

        ScreenBuffer_単文字(sb, b.x, b.y, tl);
        ScreenBuffer_単文字(sb, b.x + b.w - 1, b.y, tr);
        ScreenBuffer_単文字(sb, b.x, b.y + b.h - 1, bl);
        ScreenBuffer_単文字(sb, b.x + b.w - 1, b.y + b.h - 1, br);

        if (b.w > 2) {
            DrawHLine(sb, b.x + 1, b.y, b.w - 2, h);
            DrawHLine(sb, b.x + 1, b.y + b.h - 1, b.w - 2, h);
        }
        if (b.h > 2) {
            DrawVLine(sb, b.x, b.y + 1, b.h - 2, v);
            DrawVLine(sb, b.x + b.w - 1, b.y + 1, b.h - 2, v);
        }
    }

    void DrawLabelCentered(ScreenBuffer& sb, const UIButton& b, const std::string& text) {
        if (b.w <= 2 || b.h <= 2) return;

        const int innerW = b.w - 2;
        const int innerH = b.h - 2;

        const int tx = b.x + 1 + std::max(0, (innerW - static_cast<int>(text.size())) / 2);
        const int ty = b.y + 1 + innerH / 2;

        // 収まる範囲だけ描画
        const int maxLen = std::max(0, std::min(innerW, static_cast<int>(text.size())));
        if (maxLen <= 0) return;

        ScreenBuffer_文字列(sb, tx, ty, text.substr(0, static_cast<size_t>(maxLen)).c_str());
    }
} // namespace

void UI_DrawButton(ScreenBuffer& sb, const UIButton& b, const UIInput& in) {
    const bool over = HitTest(b, in.mouseX, in.mouseY);
    const bool pressed = over && in.mouseHeldL;

    // 見た目（ASCII枠）
    if (pressed) {
        DrawFrame(sb, b, '+', '+', '+', '+', '=', '|');
    }
    else if (over) {
        DrawFrame(sb, b, '*', '*', '*', '*', '-', '|');
    }
    else {
        DrawFrame(sb, b, '+', '+', '+', '+', '-', '|');
    }

    DrawLabelCentered(sb, b, b.label);

    // hover時はカーソル位置も分かりやすく
    if (over && b.w > 0 && b.h > 0) {
        ScreenBuffer_単文字(sb, std::clamp(in.mouseX, 0, sb.width - 1), std::clamp(in.mouseY, 0, sb.height - 1), '*');
    }
}

bool UI_ButtonClicked(const UIButton& b, const UIInput& in) {
    // 「ボタン上で左ボタンが押されたフレーム」をクリックとする（down判定）
    return HitTest(b, in.mouseX, in.mouseY) && in.mouseDownL;
}