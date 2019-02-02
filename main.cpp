#include <iostream>
#include "kd_tree.h"

int main() {
	const std::string file_name = "data.txt";
	kd_tree kd(file_name);
	std::cout << kd << '\n';
	std::vector<std::vector<double>> q = {{1.0, 0.0}};
	auto res = kd.search(q, 3);
	std::cout << "founded points: "  <<res[0].size() << '\n';
	for(int i = 0; i < res.size(); i++) {
		for(int j = 0; j < res[i].size(); j++) {
			std::cout << res[i][j] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}
