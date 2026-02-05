#include "UI.h"
#include "ScreenBuffer.h"

#include <algorithm>
#include <string>

namespace {

    // UI は 0-based、ScreenBuffer_Print は 1-based
    constexpr int ToSBX(int x0) noexcept { return x0 + 1; }
    constexpr int ToSBY(int y0) noexcept { return y0 + 1; }

    bool HitTest(const UIButton& b, int px0, int py0) noexcept {
        if (b.w <= 0 || b.h <= 0) return false;
        return (px0 >= b.x) && (py0 >= b.y) && (px0 < b.x + b.w) && (py0 < b.y + b.h);
    }

    // 固定バッファへ 1文字を書く（範囲外は捨てる）
    void PutChar0(int x0, int y0, char ch) noexcept {
        if (x0 < 0 || y0 < 0 || x0 >= WIDTH || y0 >= HEIGHT) return;
        buffer[y0][x0] = ch;
    }

    void DrawHLine0(int x0, int y0, int w, char ch) noexcept {
        if (w <= 0) return;
        const int x1 = std::clamp(x0, 0, WIDTH);
        const int x2 = std::clamp(x0 + w, 0, WIDTH);
        if (y0 < 0 || y0 >= HEIGHT) return;

        for (int x = x1; x < x2; ++x) PutChar0(x, y0, ch);
    }

    void DrawVLine0(int x0, int y0, int h, char ch) noexcept {
        if (h <= 0) return;
        const int y1 = std::clamp(y0, 0, HEIGHT);
        const int y2 = std::clamp(y0 + h, 0, HEIGHT);
        if (x0 < 0 || x0 >= WIDTH) return;

        for (int y = y1; y < y2; ++y) PutChar0(x0, y, ch);
    }

    void DrawFrame0(const UIButton& b, char tl, char tr, char bl, char br, char h, char v) noexcept {
        if (b.w < 2 || b.h < 2) return;

        // 四隅
        PutChar0(b.x, b.y, tl);
        PutChar0(b.x + b.w - 1, b.y, tr);
        PutChar0(b.x, b.y + b.h - 1, bl);
        PutChar0(b.x + b.w - 1, b.y + b.h - 1, br);

        // 辺
        if (b.w > 2) {
            DrawHLine0(b.x + 1, b.y, b.w - 2, h);
            DrawHLine0(b.x + 1, b.y + b.h - 1, b.w - 2, h);
        }
        if (b.h > 2) {
            DrawVLine0(b.x, b.y + 1, b.h - 2, v);
            DrawVLine0(b.x + b.w - 1, b.y + 1, b.h - 2, v);
        }
    }

    std::string NarrowAsciiLossy(const std::wstring& ws) {
        // 現 ScreenBuffer が char バッファなので、まずは ASCII のみ表示
        // それ以外は '?' へ（将来的にワイド対応するならここを差し替え）
        std::string s;
        s.reserve(ws.size());
        for (wchar_t wc : ws) {
            if (wc >= 0x20 && wc <= 0x7E) s.push_back(static_cast<char>(wc));
            else if (wc == L'　') s.push_back(' ');
            else s.push_back('?');
        }
        return s;
    }

    void DrawLabelCentered0(const UIButton& b, const std::wstring& text) {
        if (b.w <= 2 || b.h <= 2) return;

        const int innerW = b.w - 2;
        const int innerH = b.h - 2;

        std::string label = NarrowAsciiLossy(text);
        if (label.empty()) return;

        // innerW に収まるように切り詰め
        if (static_cast<int>(label.size()) > innerW) {
            label.resize(static_cast<std::size_t>(innerW));
        }

        const int tx0 = b.x + 1 + std::max(0, (innerW - static_cast<int>(label.size())) / 2);
        const int ty0 = b.y + 1 + innerH / 2;

        // ScreenBuffer_Print は範囲外をある程度吸収するが、tyだけは事前に落とす
        if (ty0 < 0 || ty0 >= HEIGHT) return;

        ScreenBuffer_Print(ToSBX(tx0), ToSBY(ty0), label);
    }

} // namespace

void UI_DrawButton(const UIButton& b, const UIInput& in) {; 
    const bool over = HitTest(b, in.mouseX, in.mouseY);
    const bool pressed = over && in.mouseHeldL;

    // 見た目（仮）
    if (pressed) {
        DrawFrame0(b, '+', '+', '+', '+', '=', '|');
    }
    else if (over) {
        DrawFrame0(b, '*', '*', '*', '*', '-', '|');
    }
    else {
        DrawFrame0(b, '+', '+', '+', '+', '-', '|');
    }

    DrawLabelCentered0(b, b.label);

    // ホバー中はカーソル位置に印
    if (over && b.w > 0 && b.h > 0) {
        const int mx0 = std::clamp(in.mouseX, 0, WIDTH - 1);
        const int my0 = std::clamp(in.mouseY, 0, HEIGHT - 1);
        PutChar0(mx0, my0, '*');
    }
}

bool UI_ButtonClicked(const UIButton& b, const UIInput& in) {
    return HitTest(b, in.mouseX, in.mouseY) && in.mouseDownL;
}