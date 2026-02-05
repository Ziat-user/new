#define CONIOEX
#include "conioex.h"

#include "Input.h"
#include "Scene.h"
#include "ScreenBuffer.h"

#include <string>

SceneName Setting_Update(Context& ctx) {
    (void)ctx;

    ScreenBuffer_Clear();
    ScreenBuffer_Print(1, 1, "=== 設定 ===");
    ScreenBuffer_Print(1, 3, "t: Title");
    ScreenBuffer_Print(1, 4, "ESC: Exit");

    // スペースキーの状態を表示（元コードの意図を踏襲）
    ScreenBuffer_Print(1, 6, std::to_string(inport(PK_SP)));

    if (キーボード入力(PK_T)) return SceneName::Title;
    if (キーボード入力(PK_ESC)) return SceneName::Exit;
    return SceneName::None;
}