#include "grid.h"
#include <fstream>
#include <cmath>
#include <iostream>
#define x(i) 2 * i
#define y(i) 2 * i + 1

grid::grid(const std::string file_name, const double r) : radius(r), radius_2(r * r) {
  read_points(file_name);
  build();
}

int grid::get_i_index(const size_t p) const {
	double px = points[x(p)];
	return  std::floor(std::abs(px - min_x)) / radius;
}

int grid::get_j_index(const size_t p) const {
	double py = points[y(p)];
	return std::floor(std::abs(py - min_y))/ radius;
}

void grid::build() {
	for(int i = 0; i < number_points; ++i) {
		std::pair<int, int> p = {get_i_index(i), get_j_index(i)};
		mp[p].push_back(i);
	}
}

const vec_int& grid::get_cell_points(const size_t i, const size_t j) { return mp[{i, j}]; }

void grid::reset(const double r) {
  radius = r;
  radius_2 = r * r;
  mp.clear();
  build();
}

void grid::read_points(const std::string file_name) {
	std::ifstream in(file_name);
  dimension = 2;
  //int n; int m;
	//in >> n; in >> m;
  number_points = 1000000;
  points = point(number_points * dimension);
  int time;
	for(int i = 0; i < dimension * number_points; ++i) {
  //  in >> time;
    if(i % 2 == 0) in >> time;
    in >> points[i];

    if(i % 2 == 0) {
			min_x = std::min(min_x, points[i]);
			max_x = std::max(max_x, points[i]);
		}
		if(i % 2 == 1) {
			min_y = std::min(min_y, points[i]);
			max_y = std::max(max_y, points[i]);
		}
  }
	in.close();
}
