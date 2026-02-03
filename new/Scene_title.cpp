#define CONIOEX
#include "conioex.h"

#include "Input.h"
#include "Scene.h"
#include "ScreenBuffer.h"

SceneName Title_Update(Context& ctx) {


    ScreenBuffer_クリア(ctx.screen);
    ScreenBuffer_文字列OR(ctx.screen, 0, 0, "=== TITLE ===");
    ScreenBuffer_文字列OR(ctx.screen, 0, 2, "1: Game");
    ScreenBuffer_文字列OR(ctx.screen, 0, 3, "2: Setting");
    ScreenBuffer_文字列OR(ctx.screen, 0, 4, "ESC: Exit");

    // conioex: 押下状態をポーリング
    if (キーボード入力(PK_1)) return SceneName::Game;
    if (キーボード入力(PK_2)) return SceneName::Setting;
    if (キーボード入力(PK_ESC)) return SceneName::Exit;

    return SceneName::None;
}