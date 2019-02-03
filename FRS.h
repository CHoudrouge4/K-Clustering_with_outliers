#pragma once
#include <vector>
#include <string>
#include <limits>

typedef std::vector<double> point;
typedef std::vector<int> vec_int;
typedef std::vector<point> vec_pts;

class FRS {
private:

	double min_x = std::numeric_limits<double>::max();
	double max_x = std::numeric_limits<double>::min();
	double min_y = min_x;
	double max_y = max_x;

	double raduis;

	vec_pts points;
	std::vector<vec_int> grid;

	void read_points(const std::string file_name);
	void build_2d_grid();
	FRS() {};

public:
	FRS(std::string file_name, double r);

	std::vector<int> querry_points(const point &q);
	point get_point(const size_t) const;
	vec_pts get_points(const vec_int & indices);
	void new_raduis(const double&);
};
