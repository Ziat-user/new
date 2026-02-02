#define CONIOEX
#include "conioex.h"

#include "Scene.h"
#include "ScreenBuffer.h"
int x = 3;

SceneName Title_Update(Context& ctx) {
    ScreenBuffer_クリア(ctx.screen);
    ScreenBuffer_文字列OR(ctx.screen, 0, 0, "=== TITLE ===");
    ScreenBuffer_文字列OR(ctx.screen, 0, 2, "1: Game");
    ScreenBuffer_文字列OR(ctx.screen, 0, 3, "2: Setting");
    ScreenBuffer_文字列OR(ctx.screen, 0, 4, "ESC: Exit");

    // conioex: 押下状態をポーリング
    if (inport(PK_1)) return SceneName::Game;
    if (inport(PK_2)) return SceneName::Setting;
    if (inport(PK_ESC)) return SceneName::Exit;

    return SceneName::None;
}