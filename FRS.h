#pragma once
#include <vector>
#include <string>
#include <limits>
#include <map>

typedef std::vector<double> point;
typedef std::vector<int> vec_int;
typedef std::vector<point> vec_pts;

class FRS {
private:

	double min_x = std::numeric_limits<double>::max();
	double max_x = std::numeric_limits<double>::min();
	double min_y = min_x;
	double max_y = max_x;

	double radius;
	double radius_2;

	vec_pts points;
	std::map<std::pair<int, int>, vec_int> grid;


	void read_points(const std::string file_name);
	void build_2d_grid();
	int get_grid_dimension() const;
	int get_i_index(const size_t p) const;
	int get_j_index(const size_t p) const;

	double distance_2(const int p, const int q) const;

public:
	FRS(std::string file_name, double r);

	vec_int querry_disk_r(const size_t q);
	point get_point(const size_t) const;
	vec_pts get_points(const vec_int & indices);
	vec_pts get_points();
	void new_raduis(const double&);
};
