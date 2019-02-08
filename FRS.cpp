#include "FRS.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

FRS::FRS(const std::string file_name, double r) {
	read_points(file_name);
	std::cout << min_x << ' ' << max_x << '\n';
	std::cout << min_y << ' ' << max_y << '\n';
	radius = r;
	radius_2 = r * r;
	build_2d_grid();
	covered = vec_bool(points.size());
}

double FRS::distance_2(const int p, const int q) const {
	double dx = points[p][0] - points[q][0];
	double dy = points[p][1] - points[q][1];
	return dx * dx + dy * dy;
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

int FRS::get_grid_dimension() const {
	double max_dis_x = std::abs(max_x - min_x);
	double max_dis_y = std::abs(max_y - min_y);
	double dim = std::max(max_dis_x, max_dis_y);
	return std::ceil(dim)/radius;
}

int FRS::get_i_index(const size_t p) const {
	double px = points[p][0];
	return  std::floor(std::abs(px - min_x)) / radius;
}

int FRS::get_j_index(const size_t p) const {
	double py = points[p][1];
	return std::floor(std::abs(py - min_y))/ radius;
}

void FRS::build_2d_grid() {
//	get_grid_dimension();
	for(size_t i = 0; i < points.size(); ++i) {
		std::pair<int, int> p = {get_i_index(i), get_j_index(i)};
		grid[p].push_back(i);
	}
}

void FRS::querry_disk_r(const size_t q, vec_int& res) {
	int qi = get_i_index(q);
	int qj = get_j_index(q);
	std::cout << qi << ' ' << qj << '\n';
	for(int i = qi - 3; i <= qi + 3; i++) {
		for(int j = qj - 3; j <= qj + 3; j++) {
		//	if(distance_2())
			std::pair<int, int> p = {i, j};
			auto v = grid[p];
			for(size_t l = 0; l < v.size(); ++l) {
				if(std::abs(qi - i) <= 1 && std::abs(qj - j) <= 1) {
					res.push_back(v[l]);
				} else {
					E[q].push_back(v[l]);
				}
				point_to_disks[v[l]].push_back(q);
			}
			//	res.insert(res.end(), v.begin(), v.end());
		}
	}
}

void FRS::construct_disks() {
	for(size_t i = 0; i < points.size(); ++i) {
		querry_disk_r(i, G[i]);
		disks.insert({G[i].size(), i});
	}
}

void FRS::update_disks(std::pair<int, int> & disk) {
	int size = disk.first;
	int id  = disk.second;

	disks.erase(disk);
	for(size_t i = 0; i < G[id].size(); ++i) {
		for(size_t j = 0; j < point_to_disks[G[id][i]].size(); ++j) {
		//	disks.find
		}
	}


}

std::pair<int, int> FRS::get_heaviest_disk() {
	return  *disks.begin();
}

vec_pts FRS::get_points() { return points;}
