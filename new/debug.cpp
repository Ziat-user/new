//#include <chrono>
//void showFPS(int x, int y) {
//    static std::chrono::steady_clock::time_point last_check_time;
//    static int frames_in_interval = 0;
//    static double current_fps = 0.0;
//
//    frames_in_interval++;
//    auto now = std::chrono::steady_clock::now();
//    std::chrono::duration<double> elapsed = now - last_check_time;
//
//    if (elapsed.count() >= 0.5) {
//        current_fps = frames_in_interval / elapsed.count();
//        frames_in_interval = 0;
//        last_check_time = now;
//    }
//    ScreenBuffer::Print(x, y, "FPS: " + std::to_string(current_fps));
//}