#pragma once
#include "SceneName.h"
#include "ScreenBuffer.h"

struct Context {
    // シーン間で共有したいデータがあればここに追加
    int dummy = 0;
    ScreenBuffer screen = {}; // 画面バッファ
};

using SceneFn = SceneName(*)(Context&);

SceneFn ToSceneFn(SceneName scene);