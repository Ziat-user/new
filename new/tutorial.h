#pragma once

struct UIButton;

namespace tutorial {
    void initialize();
    void update();
    bool is_finished();
    int  get_step();
    void advance_step();
    const UIButton& get_next_button();
}
