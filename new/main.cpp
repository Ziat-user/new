#include <chrono>
#define CONIOEX
#include "conioex.h"
#include <iostream>

#include "main.h"
#include "Setting.h"
#include "Scene.h"
#include "ScreenBuffer.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    if (!ziat::コンソール初期化(1)) return 0;
    
    using clock = std::chrono::steady_clock;
    using us = std::chrono::microseconds;
    const auto FRAME_DT = us(1000000 / 60); // 60fps
    auto last = clock::now();

    bool isRunning = true;

    Context ctx{};

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

            const SceneName next = update(ctx);

            // 各 Scene は ScreenBuffer_Clear/Print で buffer を作る想定。
            // ここでまとめて出力する。
            ScreenBuffer_Show();

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