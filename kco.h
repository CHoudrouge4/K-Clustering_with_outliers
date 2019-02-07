#pragma once
#include "FRS.h"
#include <unordered_map>

class KCO {

public:
	KCO(const std::string);
	void run();

private:
	FRS searcher;
	double r = 100;

	std::unordered_map<int, vec_int> mp;

};
