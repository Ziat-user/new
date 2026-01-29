#define CONIOEX
#include "conioex.h"

#include "Scene.h"
#include "ScreenBuffer.h"
#include "Input.h"

SceneName Game_Update(Context& ctx) {
    int マウス位置 = マウス位置取得();
    int 
    












    
    ScreenBuffer_文字列OR(ctx.screen, 0, 0, "=== GAME ===");
    ScreenBuffer_文字列OR(ctx.screen, 0, 2, "t: Title");
    ScreenBuffer_文字列OR(ctx.screen, 0, 3, "ESC: Exit");

    if (kbhit()) {
        const int ch = getch();
        if (ch == 't') return SceneName::Title;
        if (ch == 27)  return SceneName::Exit;
    }
    return SceneName::None;
}