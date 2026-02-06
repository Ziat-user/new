#include "UI.h"
#include "ScreenBuffer.h"

#include <algorithm>
#include <string>
#define NOMINMAX
#include <windows.h>

namespace {

    // UI は 0-based、ScreenBuffer_Print は 1-based
    constexpr int ToSBX(int x0) noexcept { return x0 + 1; }
    constexpr int ToSBY(int y0) noexcept { return y0 + 1; }

    bool HitTest(const UIButton& b, int px0, int py0) noexcept {
        if (b.w <= 0 || b.h <= 0) return false;
        return (px0 >= b.x) && (py0 >= b.y) && (px0 < b.x + b.w) && (py0 < b.y + b.h);
    }

    int DisplayWidth_WChar(wchar_t wc) noexcept {
        // 超簡易: ASCII は 1、それ以外は 2（日本語想定）
        if (wc >= 0x20 && wc <= 0x7E) return 1;
        if (wc == L'　') return 2; // 全角スペース
        return 2;
    }

    int DisplayWidth_WString(const std::wstring& ws) noexcept {
        int w = 0;
        for (wchar_t wc : ws) w += DisplayWidth_WChar(wc);
        return w;
    }

    std::wstring FitToCells(const std::wstring& ws, int maxCells) {
        if (maxCells <= 0) return L"";

        std::wstring out;
        out.reserve(ws.size());

        int used = 0;
        for (wchar_t wc : ws) {
            const int cell = DisplayWidth_WChar(wc);
            if (used + cell > maxCells) break;
            out.push_back(wc);
            used += cell;
        }
        return out;
    }

    void DrawButtonLine0(int x0, int y0, int w, char left, char fill, char right, const std::wstring& label) {
        if (w <= 0) return;
        if (y0 < 0 || y0 >= HEIGHT) return;

        const int innerW = std::max(0, w - 2);

        std::wstring lineW;
        lineW.reserve(static_cast<std::size_t>(w));

        lineW.push_back(static_cast<wchar_t>(left));

        if (label.empty()) {
            // 上/下など：横線で埋める
            lineW.append(static_cast<std::size_t>(innerW), static_cast<wchar_t>(fill));
        }
        else {
            // 中身：ラベルをセンタリング（空白で埋める）
            const std::wstring fit = FitToCells(label, innerW);
            const int labelCells = DisplayWidth_WString(fit);

            const int padL = std::max(0, (innerW - labelCells) / 2);
            const int padR = std::max(0, innerW - padL - labelCells);

            lineW.append(static_cast<std::size_t>(padL), L' ');
            lineW += fit;
            lineW.append(static_cast<std::size_t>(padR), L' ');
        }

        lineW.push_back(static_cast<wchar_t>(right));

        ScreenBuffer_Print(ToSBX(x0), ToSBY(y0), lineW);
    }

} // namespace

void UI_DrawButton(const UIButton& b, const UIInput& in) {
    const bool over = HitTest(b, in.mouseX, in.mouseY);
    const bool pressed = over && in.mouseHeldL;

    if (b.w < 2 || b.h < 2) return;

    // 枠の文字
    char tl = '+', tr = '+', bl = '+', br = '+', h = '-', v = '|';
    if (pressed) { h = '='; }
    else if (over) { tl = tr = bl = br = '*'; }

    // 上
    DrawButtonLine0(b.x, b.y, b.w, tl, h, tr, L"");

    // 中（ラベルは中央行にだけ表示）
    const int innerH = b.h - 2;
    const int labelRow = b.y + 1 + innerH / 2;

    for (int y = b.y + 1; y <= b.y + b.h - 2; ++y) {
        if (y == labelRow) {
            DrawButtonLine0(b.x, y, b.w, v, ' ', v, b.label);
        }
        else {
            DrawButtonLine0(b.x, y, b.w, v, ' ', v, L"");
        }
    }

    // 下
    DrawButtonLine0(b.x, b.y + b.h - 1, b.w, bl, h, br, L"");
}

bool UI_ButtonClicked(const UIButton& b, const UIInput& in) {
    return HitTest(b, in.mouseX, in.mouseY) && in.mouseDownL;
}