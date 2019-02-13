#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <random>
#include <chrono>
#include <ctime>
#include "FRS.h"
#include "kco.h"
#define x(i) 2 * i
#define y(i) 2 * i + 1

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

double distance2(double x1, double y1, double x2, double y2) {
	double dx = x1 - x2;
	double dy = y1 - y2;
	return dx * dx + dy * dy;
}

void naive(const point points, const int q, double r2) {
	std::vector<int> result;
	for(size_t i = 0; i < points.size()/2; ++i) if(distance2(points[x(q)], points[y(q)], points[x(i)], points[y(i)]) <= r2) result.push_back(i);
	//return result;
}

void test_frs() {
	generate_data(1000000, 2);
	clock_t begin = clock();
	FRS f("data.txt", 4);
	auto points = f.get_points();
	clock_t end = clock();
	double elapsed = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "pre time " << elapsed << '\n';

	std::cout << "start" << '\n';
	begin = clock();
	f.construct_disks();
	end = clock();
	elapsed = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "time " << elapsed << '\n';
}


int main() {

	KCO k("data.txt", 10, 0.5);

	clock_t begin = clock();
	k.run();
	clock_t end = clock();
	double elapsed = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "pre time " << elapsed << '\n';



	// begin = clock();
	// for(int i = 0; i < points.size()/2 ; ++i) {
	// 	naive(points, i,  4 * 4);
	// }
	// end = clock();
	// elapsed = double(end - begin) / CLOCKS_PER_SEC;
	// std::cout << "time " << elapsed << '\n';

	//
	// std::sort(g_res.begin(), g_res.end());
	//
	// for(size_t i = 0; i < g_res.size(); ++i) {
	// 	std::cout << g_res[i] << ' ';
	// } std::cout << '\n';
	//
	// for(size_t i = 0; i < n_res.size(); ++i) {
	// 	std::cout << n_res[i] << ' ';
	// } std::cout << '\n';
	return 0;
}
