#define CONIOEX
#include "conioex.h"

#include "Input.h"
#include "Scene.h"
#include "ScreenBuffer.h"
#include "UI.h"
#include "tutorial.h"

#include <algorithm>
#include <string>

namespace {

    struct MouseState {
        int x = 0;
        int y = 0;
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
        int test;
        return ms;
    }

    UIInput UI入力に変換(const MouseState& ms) {
        UIInput in{};
        in.mouseX = std::clamp(ms.x - 1, 0, WIDTH - 1);
        in.mouseY = std::clamp(ms.y - 1, 0, HEIGHT - 1);
        in.mouseDownL = ms.downL;
        in.mouseHeldL = ms.heldL;
        return in;
    }

    bool initialized = false;

    // ステップごとの説明文
    const wchar_t* ステップ説明(int step) {
        switch (step) {
        case 0: return L"ようこそ！ これはチュートリアルです。";
        case 1: return L"マウスでボタンをクリックして操作します。";
        case 2: return L"準備完了！ ゲームを始めましょう。";
        default: return L"";
        }
    }

} // namespace

SceneName Tutorial_Update(Context& ctx) {
    (void)ctx;

    if (!initialized) {
        tutorial::initialize();
        initialized = true;
    }

    ScreenBuffer_Clear();

    // ヘッダー
    ScreenBuffer_Print(1, 1, L"=== チュートリアル ===");

    const int step = tutorial::get_step();

    // ステップ番号
    ScreenBuffer_Print(1, 3,
        L"ステップ " + std::to_wstring(step + 1) + L" / 3");

    // 説明文
    ScreenBuffer_Print(3, 6, ステップ説明(step));

    // マウス入力取得
    const MouseState ms = マウス状態取得_簡易();
    const UIInput ui = UI入力に変換(ms);

    if (!tutorial::is_finished()) {
        // 「次へ」ボタン
        const UIButton& btnNext = tutorial::get_next_button();
        UI_DrawButton(btnNext, ui);

        if (UI_ButtonClicked(btnNext, ui)) {
            tutorial::advance_step();
        }
    }
    else {
        // チュートリアル完了 → ゲームへ遷移するボタン
        const UIButton btnStart{ 30, 20, 18, 3, L"ゲーム開始" };
        UI_DrawButton(btnStart, ui);

        if (UI_ButtonClicked(btnStart, ui)) {
            initialized = false; // 再入時にリセット
            return SceneName::Game;
        }
    }

    // フッター操作
    ScreenBuffer_Print(1, 24, L"t: タイトルに戻る   ESC: 終了");

    if (キーボード入力(PK_T)) {
        initialized = false;
        return SceneName::Title;
    }
    if (キーボード入力(PK_ESC)) {
        initialized = false;
        return SceneName::Exit;
    }

    return SceneName::None;
}