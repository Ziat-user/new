#include "debug.h"
#include "ScreenBuffer.h"

#include <chrono>
#include <cstdio>
#include <string>

// 毎フレーム呼ぶ想定。sb には「描画内容」を溜めて（出力は main で一括で行う）
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

    wchar_t buf[64]{};
    std::swprintf(buf, sizeof(buf) / sizeof(buf[0]), L"FPS: %.1f", current_fps);
    ScreenBuffer_Print(x, y, std::wstring(buf));
}