#define CONIOEX
#include "conioex.h"
#include <iostream>
#include <string>

#include "hew_console.h"
#include "Setting.h"

#include <windows.h>

namespace ziat {

	static void コンソール入力モード設定_マウス有効化() {
		HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
		if (hin == INVALID_HANDLE_VALUE || hin == nullptr) return;

		DWORD mode = 0;
		if (!GetConsoleMode(hin, &mode)) return;

		// マウス入力を有効化、クイック編集は無効化（これがONだとマウスが選択に奪われがち）
		mode |= ENABLE_MOUSE_INPUT;
		mode |= ENABLE_EXTENDED_FLAGS;
		mode &= ~ENABLE_QUICK_EDIT_MODE;

		// ウィンドウリサイズ等のイベントも必要なら拾えるが、今回は不要なので触らない
		// mode |= ENABLE_WINDOW_INPUT;

		SetConsoleMode(hin, mode);
	}

	// falseでエラーを返す on1off0
	bool コンソール初期化(bool on) {
		if (on)
			if (int start = hew_console_start(static_cast<int>(ConWindow::PRIMARY)); start != 0) {
				std::cerr << "error:" << start;
				hew_console_restore();
				return false;
			}

		コンソール入力モード設定_マウス有効化();

		// カーソル非表示
		setcursortype(NOCURSOR);
		return true;
	}

}