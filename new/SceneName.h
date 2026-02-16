#pragma once

enum class SceneName {
    None,   // 遷移なし（現のシーンを維持）
    Title,  // タイトル画
    Setting,// 設定画
    Game,   // ゲーム本編
    Tutorial, // チュートリアル
    Exit    // ゲーム終了
};