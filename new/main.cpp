#include <chrono>
#define CONIOEX
#include "conioex.h"
#include <iostream>

#include "main.h"
#include "Setting.h"
#include "Scene.h"
#include "ScreenBuffer.h"

int main() {
    if (!ziat::コンソール初期化(0)) return 0;

    using clock = std::chrono::steady_clock;
    using us = std::chrono::microseconds;
    const auto FRAME_DT = us(1000000 / 60); // 60fps
    auto last = clock::now();

    bool isRunning = true;

    Context ctx{};
    ctx.screen = ScreenBuffer_生成(80, 25, ' ');

    SceneName current = SceneName::Title;
    SceneFn update = ToSceneFn(current);

    while (isRunning) {
        const auto now = clock::now();
        const auto elapsed = std::chrono::duration_cast<us>(now - last);

        if (elapsed >= FRAME_DT) {
            last = now;

            if (!update) {
                isRunning = false;
                break;
            }
            ScreenBuffer_クリア(ctx.screen);
            const SceneName next = update(ctx);

            ScreenBuffer_出力(ctx.screen);

            if (next != SceneName::None) {
                if (next == SceneName::Exit) {
                    isRunning = false;
                }
                else {
                    current = next;
                    update = ToSceneFn(current);
                }
            }
        }
    }

    hew_console_restore();
    return 0;
}