#include <iostream>
#include <string>
#include <random>
#include "game.h"

namespace gamecore{
	
	void ‰Šú‰»() {
		if (CPU.empty()) return;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, static_cast<int>(CPU.size()) - 1);

		for (auto& npc : CPU) npc.^‹U = false;
		//¶‘¤‚Éó‚¯æ‚é•Ï”‰E‘¤‚É—^‚¦‚é”z—ñŒn
		int idx = dist(gen);
		CPU[idx].^‹U = true;
	}
}