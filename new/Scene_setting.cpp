#define CONIOEX
#include "conioex.h"

#include "Scene.h"
#include "ScreenBuffer.h"

SceneName Setting_Update(Context& ctx) {
    ScreenBuffer_ƒNƒŠƒA(ctx.screen);
    ScreenBuffer_•¶Žš—ñOR(ctx.screen, 0, 0, "=== SETTING ===");
    ScreenBuffer_•¶Žš—ñOR(ctx.screen, 0, 2, "t: Title");
    ScreenBuffer_•¶Žš—ñOR(ctx.screen, 0, 3, "ESC: Exit");

    if (kbhit()) {
        const int ch = getch();
        if (ch == 't') return SceneName::Title;
        if (ch == 27)  return SceneName::Exit;
    }
    return SceneName::None;
}