#include "FRS.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
#define x(i) 2 * i
#define y(i) 2 * i + 1

FRS::FRS(const std::string file_name, const double r) : grid(file_name, r) {
	std::cout << d_size << '\n';
	G = std::vector<vec_pair>(number_points);
	E = std::vector<vec_pair>(number_points);
	point_to_disks = std::vector<vec_int>(number_points);
	disks_sizes = std::vector<int>(number_points);
}

void FRS::init() {
	//d_size = new int(sizeof(int));
	//d_size = number_points;
	std::cout << "number_points " <<  number_points << '\n';
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
	std::cout << "disk construction began " << '\n';
	for(int q = 0; q < number_points; ++q) {
		//querry_disk_r(q, G[q]);
		int qi = get_i_index(q);
		int qj = get_j_index(q);
		//std::cout << qi << ' ' << qj << '\n';
		for(int i = qi - 3; i <= (qi + 3); i++) {
			for(int j = qj - 3; j <= (qj + 3); j++) {
				const vec_int& v = get_cell_points(i, j);
				if((std::abs(qi - i) <= 1) && (std::abs(qj - j) <= 1)) {
					G[q].push_back({i, j});
				} else {
					E[q].push_back({i, j});
				}
				disks_sizes[q] += v.size();
				//	point_to_disks[v[l]].push_back(q);
				cell_to_disk[std::make_pair(i, j)].push_back(q);
			}
		}

		disks.insert({disks_sizes[q], q});
	}
}

/**
 	given a cell p, loop over all the disks where this cell bellong
	ans decrese its size from the cell.
*/
void FRS::mark_corresponding_disk(std::pair<int, int> &p) {
	// /std::cout << "c2d " << cell_to_disk[p].size() << '\n';
	for(size_t j = 0; j < cell_to_disk[p].size(); ++j) {
	 	int d_id = cell_to_disk[p][j]; // a disk to where the cell bellon
		disks.erase(std::make_pair(disks_sizes[d_id], d_id));
		disks_sizes[d_id] -= mp[p].size();
		if(disks_sizes[d_id] > 0)
			disks.insert({disks_sizes[d_id], d_id});
	}
}

void FRS::update_disks(std::pair<int, int>  disk) {
	std::cout << "update disk begin" << '\n';
	covered += disk.first;
	int id  = disk.second;
	//std::cout << G.size() << std::endl;
	disks_sizes[id] = 0;
	disks.erase(disk);
//	std::cout << "G id size " << id << ' ' << G[id].size() << '\n';
	for(size_t i = 0; i < G[id].size(); ++i) {
		auto p = G[id][i]; // pair that represent a sell
		auto pe = E[id][i];
		mark_corresponding_disk(p);
		mark_corresponding_disk(pe);
	}
}

void FRS::new_raduis(const double r) {
	covered = 0;
	reset(r);
	init();
	construct_disks();
}

double FRS::lower_bound() {
		return std::max(std::abs(max_x - min_x), std::abs(max_y - min_y));
}

std::pair<int, int> FRS::get_heaviest_disk() { return  *disks.begin(); }
int FRS::get_covered() { return covered; }
const std::vector<double>& FRS::get_points() { return points; }
const int& FRS::data_size() { return d_size; }

vec_pts FRS::get_g_points(const int id) {
	vec_pts res(G[id].size() + E[id].size());
	for(size_t i = 0; i < G[id].size(); ++i) {
		for(size_t j = 0; j < mp[G[id][i]].size(); ++j) {
			int pi = mp[G[id][i]][j];
			res[i].push_back(points[x(pi)]);
			res[i].push_back(points[y(pi)]);
		}
	}

	for(size_t i = 0; i < E[id].size(); ++i) {
		for(size_t j = 0; j < mp[E[id][i]].size(); ++j) {
			int pi = mp[E[id][i]][j];
			//std::cout << pi << std::endl;
			res[G[id].size() + i].push_back(points[x(pi)]);
			res[G[id].size() + i].push_back(points[y(pi)]);
		}
	}


	return res;
}
