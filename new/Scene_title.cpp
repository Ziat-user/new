#define CONIOEX
#include "conioex.h"

#include "Scene.h"
#include "ScreenBuffer.h"
int x = 3;

SceneName Title_Update(Context& ctx) {
    ScreenBuffer_ƒNƒŠƒA(ctx.screen);
    ScreenBuffer_•¶Žš—ñOR(ctx.screen, 0, 0, "=== TITLE ===");
    ScreenBuffer_•¶Žš—ñOR(ctx.screen, 0, 2, "1: Game");
    ScreenBuffer_•¶Žš—ñOR(ctx.screen, 0, 3, "2: Setting");
    ScreenBuffer_•¶Žš—ñOR(ctx.screen, 0, 4, "ESC: Exit");

    if (kbhit()) {
        const int ch = getch();
        if (ch == '1') return SceneName::Game;
        if (ch == '2') return SceneName::Setting;
        if (ch == 27)  return SceneName::Exit; // ESC
    }
    return SceneName::None;
}