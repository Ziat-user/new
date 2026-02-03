#include <iostream>
#include <vector>
#include <string>
#include <random>

namespace gamescene{
	void 初期化() {
		inline static std::vector<std::string>CPU(5);
		std::random_device rd;                          // ハードウェア乱数を使って初期化
		std::mt19937 gen(rd());                         // メルセンヌ・ツイスタによる乱数生成器
		std::uniform_int_distribution<> dist(0, sizeof(CPU) / sizeof(CPU[0]) - 1);
	}
}