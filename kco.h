#pragma once
#include "FRS.h"

class KCO {
public:
	KCO(const std::string file_name, const int num_clusters, const double alpha);
	bool cover();
	void run();
	void print_clusters();

private:
	FRS searcher;
	int k;
	double r = 1000;
	int p;
	std::vector<int> clussters;
};
