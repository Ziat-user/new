#define CONIOEX
#include "conioex.h"

#include "Scene.h"
#include "ScreenBuffer.h"
#include "Input.h"
#include "debug.h"
#include "UI.h"

#include <algorithm>
#include <string>

namespace { 

    struct MouseState {
        int x = 0;
        int y = 0;
        bool downL = false;
        bool downM = false;
        bool downR = false;
        bool heldL = false;
        bool heldM = false;
        bool heldR = false;
    };

    MouseState マウス状態取得() {
        MouseState ms{};

        const int packed = マウス位置取得();
        ms.x = (packed >> 8) & 0xFF;
        ms.y = packed & 0xFF;

        const int mouse = マウス入力();
        const int down = mouse & 0b111;
        const int held = (mouse >> 3) & 0b111;

        ms.downL = (down & 0b001) != 0;
        ms.downM = (down & 0b010) != 0;
        ms.downR = (down & 0b100) != 0;

        ms.heldL = (held & 0b001) != 0;
        ms.heldM = (held & 0b010) != 0;
        ms.heldR = (held & 0b100) != 0;

        return ms;
    }

    UIInput UI入力に変換(const ScreenBuffer& sb, const MouseState& ms) {
        UIInput in{};

        // clampに渡す型を int で統一（これが重要）
        const int maxX = (sb.width > 0) ? (sb.width - 1) : 0;
        const int maxY = (sb.height > 0) ? (sb.height - 1) : 0;

        // conioex側は 1-based なので 0-based へ
        in.mouseX = std::clamp(static_cast<int>(ms.x - 1), 0, maxX);
        in.mouseY = std::clamp(static_cast<int>(ms.y - 1), 0, maxY);

        in.mouseDownL = ms.downL;
        in.mouseHeldL = ms.heldL;

        return in;
    }

    void ゲームUI描画(ScreenBuffer& sb, const MouseState& ms) {
        ScreenBuffer_文字列OR(sb, 0, 0,
            std::string("Mouse: x=") + std::to_string(ms.x) + " y=" + std::to_string(ms.y));

        ScreenBuffer_文字列OR(sb, 0, 1,
            std::string("MouseBtn down : L=") + (ms.downL ? "1" : "0") +
            " M=" + (ms.downM ? "1" : "0") +
            " R=" + (ms.downR ? "1" : "0"));

        ScreenBuffer_文字列OR(sb, 0, 2,
            std::string("MouseBtn held : L=") + (ms.heldL ? "1" : "0") +
            " M=" + (ms.heldM ? "1" : "0") +
            " R=" + (ms.heldR ? "1" : "0"));

        showFPS(sb, 0, 3);

        ScreenBuffer_文字列OR(sb, 0, 5, "=== GAME ===");
        ScreenBuffer_文字列OR(sb, 0, 7, "t: Title");
        ScreenBuffer_文字列OR(sb, 0, 8, "ESC: Exit");
    }

    SceneName 次シーン判定(const UIButton& toTitle, const UIButton& exitBtn, const UIInput& ui) {
        if (UI_ButtonClicked(toTitle, ui)) return SceneName::Title;
        if (UI_ButtonClicked(exitBtn, ui)) return SceneName::Exit;

        if (キーボード入力(PK_T)) return SceneName::Title;
        if (キーボード入力(PK_ESC)) return SceneName::Exit;

        return SceneName::None;
    }

} // namespace

SceneName Game_Update(Context& ctx) {
    ScreenBuffer_クリア(ctx.screen);

    const MouseState mouse = マウス状態取得();
    const UIInput ui = UI入力に変換(ctx.screen, mouse);

    ゲームUI描画(ctx.screen, mouse);

    const UIButton btnTitle{ 0, 12, 16, 3, L"ﾀｲﾄﾙ" };
    const UIButton btnExit{ 0, 16, 16, 3, L"ｼｭｳﾘｮｳ" };

    UI_DrawButton(ctx.screen, btnTitle, ui);
    UI_DrawButton(ctx.screen, btnExit, ui);

    return 次シーン判定(btnTitle, btnExit, ui);
}