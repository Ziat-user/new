#define CONIOEX
#include "conioex.h"

#include "Input.h"
#include "Scene.h"
#include "ScreenBuffer.h"

SceneName Setting_Update(Context& ctx) {
    ScreenBuffer_クリア(ctx.screen);
    ScreenBuffer_文字列OR(ctx.screen, 0, 0, "=== SETTING ===");
    ScreenBuffer_文字列OR(ctx.screen, 0, 2, "t: Title");
    ScreenBuffer_文字列OR(ctx.screen, 0, 3, "ESC: Exit");
    ScreenBuffer_文字列OR(ctx.screen, 0, 4, std::to_string(inport(PK_SP)));

    if (キーボード入力(PK_T))return SceneName::Title;
    if (キーボード入力(PK_ESC))return SceneName::Exit;
    return SceneName::None;
}