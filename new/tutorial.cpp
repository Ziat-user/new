#include "tutorial.h"
#include "UI.h"

namespace tutorial {

    // チュートリアルのステップ管理
    static int currentStep = 0;
    static constexpr int TOTAL_STEPS = 3;
    static bool finished = false;

    // 各ステップ用ボタン
    static UIButton btnNext{ 30, 20, 18, 3, L"次へ" };
    static UIButton btnCPU1{};

    void initialize() {
        currentStep = 0;
        finished = false;
    }

    void update() {
        // ステップ進行は Scene_tutorial 側のクリック判定で呼ばれる
    }

    bool is_finished() {
        return finished;
    }

    int get_step() {
        return currentStep;
    }

    void advance_step() {
        ++currentStep;
        if (currentStep >= TOTAL_STEPS) {
            finished = true;
        }
    }

    const UIButton& get_next_button() {
        return btnNext;
    }

} // namespace tutorial