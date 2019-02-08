#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <random>
#include <chrono>
#include <ctime>
#include "FRS.h"

typedef std::vector<double> point;


#define RANGE 100
const double epsilon = 0.5;

static std::random_device rd;
static std::mt19937 gen(rd());

point generate_point(const int dim) {
	static std::uniform_int_distribution<> dis(-RANGE, RANGE);
	point p(dim);
	for(int j = 0; j < dim; ++j) p[j] = dis(gen);
	return p;
}

std::string point_to_string(const point p) {
	std::ostringstream o;
	for(size_t i = 0; i < p.size() - 1; ++i)
		o << p[i] << ' ';
	o << p[p.size() - 1];
	return o.str();
}

void generate_data(const int size, const int dim) {
	std::ofstream out("data.txt");
	out << size << ' ' << dim << '\n';
	for(int i = 0; i < size; i++) {
		point p = generate_point(dim);
		out << point_to_string(p) << '\n';
	}
	out.close();
}

double distance2(point x, point y) {
	double sum = 0.0;
	for(size_t j = 0; j < x.size(); ++j) sum += (x[j] - y[j] ) * (x[j] - y[j]);
	return sum;
}

std::vector<int> naive(const std::vector<point> points, const int q, double r2) {
	std::vector<int> result;
	for(size_t i = 0; i < points.size(); ++i) if(distance2(points[q], points[i]) <= r2) result.push_back(i);
	return result;
}

int main() {

	generate_data(100, 2);
	FRS f("data.txt", 4);
	auto points = f.get_points();

	clock_t begin = clock();
	vec_int g_res;
	f.querry_disk_r(0, g_res);
	clock_t end = clock();
	double elapsed = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "time " << elapsed << '\n';

	begin = clock();
	auto n_res = naive(points, 0,  4 * 4);
	end = clock();
	elapsed = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "time " << elapsed << '\n';


	std::sort(g_res.begin(), g_res.end());

	for(size_t i = 0; i < g_res.size(); ++i) {
		std::cout << g_res[i] << ' ';
	} std::cout << '\n';

	for(size_t i = 0; i < n_res.size(); ++i) {
		std::cout << n_res[i] << ' ';
	} std::cout << '\n';

	return 0;
}
