#include "kco.h"
#include <cmath>
#include <iostream>

KCO::KCO(const std::string file_name, const int num_clusters, const double alpha)
: searcher(file_name, 1.5)
, k(num_clusters)
, p(std::ceil(1 - alpha) * searcher.get_points().size())
, clussters(num_clusters)
{}

bool KCO::cover() {
	  // O(n), O(n log n)
	for(int i = 0; i < k; ++i) {
		auto G_i = searcher.get_heaviest_disk(); //gi  O(log n)
		clussters[i] = G_i.second;
		// mark Ei				   O(|Ei|)
		// updates all the disk    O()
		searcher.update_disks(G_i);
	}

	for(int i = 0; i < k; ++i) {
		std::cout << clussters[i] << '\n';
	}

	std::cout << "covered points " << searcher.get_covered() << '\n';
	if(searcher.get_covered() >= p) return true;
	return false;
}

void KCO::run() {
	double lower = 1;
	double upper = searcher.lower_bound()/2;
	double r = (lower + upper)/2;
	while(lower < upper) {
	//searcher.construct_disks();
		searcher.new_raduis(r);
		if(cover()) {
			lower += 1;
			upper = r;
		} else {
			lower = r;
		}

		r = (lower + upper)/2;
		std::cout << "what is r " << r << '\n';
	}
	//searcher.new_raduis(r);
}

void KCO::print_clusters() {
	for(size_t i = 0; i < clussters.size(); ++i) {
		auto vec = searcher.get_g_points(clussters[i]);
		//std::cout << "clusster " << i << '\n';
		for(size_t j = 0; j < vec.size(); ++j) {
				if(vec[j].size() != 0)
					std::cout << vec[j][0] << ' ' << vec[j][1] << ' ' << i + 4 << '\n';
		}
	}
}
