#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace file {
	std::optional<std::string> ReadAllText(const std::string& path) {
		std::ifstream ifs(path, std::ios::in | std::ios::binary);
		if (!ifs) return std::nullopt;

		std::string s;
		ifs.seekg(0, std::ios::end);
		const std::streamoff size = ifs.tellg();
		if (size < 0) return std::nullopt;
		ifs.seekg(0, std::ios::beg);

		s.resize(static_cast<size_t>(size));
		if (!s.empty()) {
			ifs.read(s.data(), static_cast<std::streamsize>(s.size()));
			if (!ifs) return std::nullopt;
		}
		return s;
	}

	std::optional<std::vector<std::string>> ReadAllLines(const std::string& path) {
		std::ifstream ifs(path);
		if (!ifs) return std::nullopt;

		std::vector<std::string> lines;
		std::string line;
		while (std::getline(ifs, line)) {
			// CRLF対策（末尾の '\r' を除去）
			if (!line.empty() && line.back() == '\r') line.pop_back();
			lines.push_back(std::move(line));
		}

		if (!ifs.eof()) return std::nullopt; // 途中でI/Oエラー
		return lines;
	}

	void ファイル_文字列(const std::string& 文字列) {
		//コメント
		
		
	}

} // namespace file