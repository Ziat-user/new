#include "debug.h"
#include "ScreenBuffer.h"

#include <chrono>
#include <cstdio>
#include <string>

// 毎フレーム呼ぶ想定。sb には「書くだけ」（出力は main 側で一括実行）
void showFPS(ScreenBuffer& sb, int x, int y) {
    using clock = std::chrono::steady_clock;

    static clock::time_point last_check_time = clock::now();
    static int frames_in_interval = 0;
    static double current_fps = 0.0;

    ++frames_in_interval;

    const auto now = clock::now();
    const std::chrono::duration<double> elapsed = now - last_check_time;

    if (elapsed.count() >= 0.5) {
        current_fps = static_cast<double>(frames_in_interval) / elapsed.count();
        frames_in_interval = 0;
        last_check_time = now;
    }

    char buf[64]{};
    std::snprintf(buf, sizeof(buf), "FPS: %.1f", current_fps);
    ScreenBuffer_Print(x, y, buf);
}