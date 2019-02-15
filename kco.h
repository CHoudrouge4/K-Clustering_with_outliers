#pragma once
#include "FRS.h"

class KCO {
public:
	KCO(const std::string file_name, const int num_clusters, const double alpha);
	KCO(const std::string file_name, const int num_clusters, const double alpha, int num_pts);
	/**
	* Apply clustering given a radius
	*/
	bool cover();

	/**
	* Binary search for the right radius
	*/
	void run();
	void test();
	// print the clussters
	void print_clusters();

private:
	FRS searcher;
	int k;
	double r = 1000;
	int p;
	// stores the id of the diks as a representation of the clusster.
	std::vector<int> clussters;
};
