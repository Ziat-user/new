#pragma once

enum class SceneName {
    None,   // 遷移なし（今のシーンを維持）
    Title,  // タイトルへ
    Setting,// 設定画面
    Game,   // ゲーム本編へ
    Exit    // ゲーム終了
};