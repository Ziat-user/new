#define CONIOEX
#include "conioex.h"

#include "Input.h"
#include "Scene.h"
#include "ScreenBuffer.h"
#include "UI.h"

#include <algorithm>

namespace {

    struct MouseState {
        int x = 0; // 1-based (conioex)
        int y = 0; // 1-based (conioex)
        bool downL = false;
        bool heldL = false;
    };

    MouseState マウス状態取得_簡易() {
        MouseState ms{};

        const int packed = マウス位置取得();
        ms.x = (packed >> 8) & 0xFF;
        ms.y = packed & 0xFF;

        const int mouse = マウス入力();
        const int down = mouse & 0b111;
        const int held = (mouse >> 3) & 0b111;

        ms.downL = (down & 0b001) != 0;
        ms.heldL = (held & 0b001) != 0;

        return ms;
    }

    UIInput UI入力に変換_固定SB(const MouseState& ms) {
        UIInput in{};

        // conioex は 1-based、UI は 0-based
        in.mouseX = std::clamp(ms.x - 1, 0, WIDTH - 1);
        in.mouseY = std::clamp(ms.y - 1, 0, HEIGHT - 1);

        in.mouseDownL = ms.downL;
        in.mouseHeldL = ms.heldL;

        return in;
    }

} // namespace

SceneName Title_Update(Context& ctx) {
    (void)ctx;

    ScreenBuffer_Clear();
    ScreenBuffer_Print(1, 1, L"=== タイトル ===");

    // 仮置きボタン（座標は 0-based）
    const UIButton btnGame{ 2, 4, 18, 3, L"ゲーム" };
    const UIButton btnTutorial{ 2, 8, 18, 3, L"チュートリアル" };
    const UIButton btnSetting{ 2, 12, 18, 3, L"SETTING" };
    const UIButton btnExit{ 2, 16, 18, 3, L"EXIT" };

    const MouseState ms = マウス状態取得_簡易();
    const UIInput ui = UI入力に変換_固定SB(ms);

    UI_DrawButton(btnGame, ui);
    UI_DrawButton(btnTutorial, ui);
    UI_DrawButton(btnSetting, ui);
    UI_DrawButton(btnExit, ui);

    // キー操作も残す（仮）
    ScreenBuffer_Print(1, 20, L"1: ゲーム   2: チュートリアル   3: 設定   ESC: 終了");

    if (UI_ButtonClicked(btnGame, ui))     return SceneName::Game;
    if (UI_ButtonClicked(btnTutorial, ui)) return SceneName::Tutorial;
    if (UI_ButtonClicked(btnSetting, ui))  return SceneName::Setting;
    if (UI_ButtonClicked(btnExit, ui))     return SceneName::Exit;

    if (キーボード入力(PK_1)) return SceneName::Game;
    if (キーボード入力(PK_2)) return SceneName::Tutorial;
    if (キーボード入力(PK_3)) return SceneName::Setting;
    if (キーボード入力(PK_ESC)) return SceneName::Exit;

    return SceneName::None;
}