#include "FRS.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
#define x(i) 2 * i
#define y(i) 2 * i + 1

FRS::FRS(const std::string file_name, const double r) : grid(file_name, r) {
	init();
}

void FRS::init() {
	G = std::vector<vec_pair>(number_points);
	E = std::vector<vec_pair>(number_points);
	point_to_disks = std::vector<vec_int>(number_points);
	disks_sizes = std::vector<int>(number_points);
}

double FRS::distance_2(const int p, const int q) const {
	double dx = points[x(p)] - points[x(q)];
	double dy = points[y(p)] - points[y(q)];
	return dx * dx + dy * dy;
}

void FRS::construct_disks() {
	for(int q = 0; q < number_points; ++q) {
		//querry_disk_r(q, G[q]);
		int qi = get_i_index(q);
		int qj = get_j_index(q);
		for(int i = qi - 3; i <= qi + 3; i++) {
			for(int j = qj - 3; j <= qj + 3; j++) {
				const vec_int& v = get_cell_points(i, j);
				if(std::abs(qi - i) <= 1 && std::abs(qj - j) <= 1) {
					G[q].push_back({i, j});
				 } else  {
					E[q].push_back({i, j});
				}
				disks_sizes[q] += v.size();
				//	point_to_disks[v[l]].push_back(q);
			}
		}
		disks.insert({disks_sizes[q], q});
	}
}

void FRS::mark_corresponding_disk(int p) {
	for(size_t j = 0; j < point_to_disks[p].size(); ++j) {
		int d_id = point_to_disks[p][j];
		disks.erase(std::make_pair(disks_sizes[d_id], d_id));
		disks_sizes[d_id]--;
		assert(disks_sizes[d_id] >= 0);
		disks.insert({disks_sizes[d_id], d_id});
	}
}

void FRS::update_disks(std::pair<int, int> & disk) {
	covered += disk.first;
	int id  = disk.second;
	disks_sizes[id] = 0;
	disks.erase(disk);
	for(size_t i = 0; i < G[id].size(); ++i) {
		//int p = G[id][i];
		//int pe = E[id][i];
		//mark_corresponding_disk(p);
		//mark_corresponding_disk(pe);
	}
}

void FRS::new_raduis(const double r) {
	reset(r);
	init();
	construct_disks();
}

std::pair<int, int> FRS::get_heaviest_disk() { return  *disks.begin(); }
int FRS::get_covered() { return covered; }
const std::vector<double>& FRS::get_points() { return points; }
