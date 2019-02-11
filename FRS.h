#pragma once
#include <vector>
#include <string>
#include <limits>
#include <map>
#include <unordered_map>
#include <set>
#include "grid.h"

template <typename T>
struct cmp {
	bool operator()(const T& lhs, const T& rhs) { return lhs > rhs; }
};

class FRS : public grid {
private:
	int covered = 0;
	double radius;
	double radius_2;
	vec_int disks_sizes;
	std::vector<vec_pair> G;
	std::vector<vec_pair> E;
	std::vector<vec_int> point_to_disks;
	std::set<std::pair<int, int>, cmp<std::pair<int, int>>> disks;

	double distance_2(const int p, const int q) const;
	void mark_corresponding_disk(int p);
	void init();
public:
	FRS(const std::string file_name, const double r);
	FRS() {};
	//void querry_disk_r(const size_t q, vec_int& res);
	void construct_disks();
	void update_disks(std::pair<int, int> &disk);
	std::pair<int, int> get_heaviest_disk();
	void new_raduis(const double);
	int get_covered();
	const std::vector<double>& get_points();
};
