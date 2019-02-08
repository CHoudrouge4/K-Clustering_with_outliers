#pragma once
#include "FRS.h"
#include <unordered_map>

class KCO {

public:
	KCO(const std::string file_name, const int num_clusters);
	void run();

private:
	FRS searcher;
	int k;
	double r = 100;



	std::unordered_map<int, vec_int> mp;

};
