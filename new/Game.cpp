#include <iostream>
#include <vector>
#include <string>
#include <random>

namespace gamescene{
	struct NPCステート {
		bool 真偽;
		std::string 名前;
		std::vector<int> 性格;
	};
	void 初期化() {
		static std::vector<bool> CPU(5); 

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 1);
		for (size_t st = 0; st < CPU.size(); ++st) {
			CPU[st] = dist(gen);
		}
	}
}