#include "FRS.h"
#include <fstream>
#include <iostream>
#include <algorithm>

FRS::FRS(std::string file_name, double r) {
	read_points(file_name);
	std::cout << min_x << ' ' << max_x << '\n';
	std::cout << min_y << ' ' << max_y << '\n';

}

void FRS::read_points(const std::string file_name) {
	std::cout << "Start reading points" << '\n';
	std::ifstream in(file_name);
	int n; int m;
	in >> n; in >> m;
	points = vec_pts(n, point(m));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			in >> points[i][j];
			if(j == 0) {
				min_x = std::min(min_x, points[i][j]);
				max_x = std::max(max_x, points[i][j]);
			}
			if(j == 1) {
				min_y = std::min(min_y, points[i][j]);
				max_y = std::max(max_y, points[i][j]);
			}
		}
	in.close();
	std::cout << "Finish Reading Points" << '\n';
}

void FRS::build_2d_grid() {
}
