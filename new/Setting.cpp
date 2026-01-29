#define CONIOEX
#include "conioex.h"
#include <iostream>
#include <string>

#include "hew_console.h"
#include "Setting.h"

namespace ziat {

	//falseでエラーを返す on1off0
	bool コンソール初期化(bool on) {
		if (on)
		if (int start = hew_console_start(static_cast<int>(ConWindow::PRIMARY)); start != 0) {
			std::cerr << "error:" << start;
			hew_console_restore();
			return false;
		}
		//カーソル非表示
		setcursortype(NOCURSOR);
		return true;
	}

}