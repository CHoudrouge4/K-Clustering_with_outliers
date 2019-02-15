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

/**
* generate a point of given dimension
*/
point generate_point(const int dim) {
	static std::uniform_int_distribution<> dis(-RANGE, RANGE);
	point p(dim);
	for(int j = 0; j < dim; ++j) p[j] = dis(gen);
	return p;
}

/**
* Generate clusstered_data
*/
void generate_clusstered_points(int size, int dim) {
	std::normal_distribution<> d1(5, 3);
	std::normal_distribution<> d2(-10, 3);
	std::normal_distribution<> d3(-4, 3);
	std::ofstream out("clusstered_data.txt");
	//out << size << ' ' << dim << '\n';
	for(int i = 0; i < size; i++) {
		if(i % 3 == 0)
			out << d1(gen) << ' ' << d1(gen) << '\n';
		if(i % 3 == 1)
			out << d2(gen) << ' ' << d2(gen) << '\n';
		if(i % 3 == 2)
			out << d3(gen) << ' ' << d3(gen) << '\n';
	}
	out.close();
}

/**
* return a string representation of a point
*/
std::string point_to_string(const point &p) {
	std::ostringstream o;
	for(size_t i = 0; i < p.size() - 1; ++i)
		o << p[i] << ' ';
	o << p[p.size() - 1];
	return o.str();
}

/**
* Generate data uniformally at random
*/
void generate_data(const int size, const int dim) {
	std::ofstream out("data.txt");
	out << size << ' ' << dim << '\n';
	for(int i = 0; i < size; i++) {
		point p = generate_point(dim);
		out << point_to_string(p) << '\n';
	}
	out.close();
}

/**
* Compute the distance square
*/
double distance2(double x1, double y1, double x2, double y2) {
	double dx = x1 - x2;
	double dy = y1 - y2;
	return dx * dx + dy * dy;
}

/**
* Naive way to get the points in a qiven raduis^2
*/
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

	 std::string twitter = "./dataset/twitter_1000000.txt";
	 const int num_pts = 100;
	 int clusster_number = 3;
	 generate_clusstered_points(num_pts, 2);
	 std::string file_name = twitter;
	 clock_t begin = clock();
	 KCO k(file_name, clusster_number, 1);
	 k.run();
	 clock_t end = clock();
	 double elapsed = double(end - begin) / CLOCKS_PER_SEC;
	 std::cout << "pre time " << elapsed << '\n';

	 return 0;
}
