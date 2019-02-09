#pragma once
#include "FRS.h"

class KCO {

public:
	KCO(const std::string file_name, const int num_clusters, const double alpha);
	bool cover();
	void run();

private:
	FRS searcher;
	int k;
	double r = 100;
	int p;
	std::vector<vec_int> mp;
};
