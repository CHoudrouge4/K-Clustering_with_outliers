#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <random>
#include <chrono>
#include "FRS.h"

typedef std::vector<double> point;


#define RANGE 20
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

std::vector<int> naive(const std::vector<point> points, point &q, double r2) {
	std::vector<int> result;
	for(size_t i = 0; i < points.size(); ++i) if(distance2(q, points[i]) <= r2) result.push_back(i);
	return result;
}

int main() {

	generate_data(100, 2);
	FRS("data.txt", 4);

	return 0;
}
