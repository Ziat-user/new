#define CONIOEX
#include "conioex.h"

#include "Scene.h"
#include "ScreenBuffer.h"
#include "Input.h"

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

    void ゲームUI描画(const MouseState& ms) {
        ScreenBuffer_Print(1, 1, L"Mouse: x=" + std::to_wstring(ms.x) + L" y=" + std::to_wstring(ms.y));

        ScreenBuffer_Print(1, 2,
            std::wstring(L"MouseBtn down : L=") + (ms.downL ? L"1" : L"0") +
            L" M=" + (ms.downM ? L"1" : L"0") +
            L" R=" + (ms.downR ? L"1" : L"0"));

        ScreenBuffer_Print(1, 3,
            std::wstring(L"MouseBtn held : L=") + (ms.heldL ? L"1" : L"0") +
            L" M=" + (ms.heldM ? L"1" : L"0") +
            L" R=" + (ms.heldR ? L"1" : L"0"));

        ScreenBuffer_Print(1, 6, L"=== GAME ===");
        ScreenBuffer_Print(1, 8, L"t: Title");
        ScreenBuffer_Print(1, 9, L"ESC: 終了");
    }

} // namespace

SceneName Game_Update(Context& ctx) {
    (void)ctx;

    ScreenBuffer_Clear();

    const MouseState mouse = マウス状態取得();
    ゲームUI描画(mouse);

    if (キーボード入力(PK_T)) return SceneName::Title;
    if (キーボード入力(PK_ESC)) return SceneName::Exit;

    return SceneName::None;
}