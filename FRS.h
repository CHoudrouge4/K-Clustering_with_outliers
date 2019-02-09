#pragma once
#include <vector>
#include <string>
#include <limits>
#include <map>
#include <unordered_map>
#include <set>

typedef std::vector<double> point;
typedef std::vector<int> vec_int;
typedef std::vector<point> vec_pts;
typedef std::vector<bool> vec_bool;

template <typename T>
struct cmp {
	bool operator()(const T& lhs, const T& rhs) { return lhs > rhs; }
};

class FRS {
private:
	int covered = 0;

	double min_x = std::numeric_limits<double>::max();
	double max_x = std::numeric_limits<double>::min();
	double min_y = min_x;
	double max_y = max_x;
	double radius;
	double radius_2;

	vec_pts points;
	vec_int sizes;

	std::map<std::pair<int, int>, vec_int> grid;

	std::vector<vec_int> G;
	std::vector<vec_int> E;
	std::vector<vec_int> point_to_disks;
	std::set<std::pair<int, int>, cmp<std::pair<int, int>>> disks;

	void read_points(const std::string file_name);
	void build_2d_grid();
	int get_grid_dimension() const;
	int get_i_index(const size_t p) const;
	int get_j_index(const size_t p) const;

	double distance_2(const int p, const int q) const;

public:
	FRS(const std::string file_name, double r);
	FRS() {};

	void querry_disk_r(const size_t q, vec_int& res);
	void construct_disks();
	void update_disks(std::pair<int, int> &disk);

	std::pair<int, int> get_heaviest_disk();
	point get_point(const size_t) const;
	vec_pts get_points(const vec_int & indices);
	vec_pts get_points();
	void new_raduis(const double&);
	
};