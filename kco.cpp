#include "kco.h"
#include <cmath>
#include <iostream>

KCO::KCO(const std::string file_name, const int num_clusters, const double alpha)
: searcher(file_name, r)
, k(num_clusters)
, p(std::ceil(1 - alpha) * searcher.get_points().size())
, clussters(num_clusters)
{}

bool KCO::cover() {
	  // O(n), O(n log n)
	for(int i = 0; i < k; ++i) {
		std::cout << "data size " <<  searcher.data_size() << '\n';
		auto G_i = searcher.get_heaviest_disk(); //gi  O(log n)
		// mark Ei				   O(|Ei|)
		// updates all the disk    O()
		//	clussters[i].push_back(g_i);
		searcher.update_disks(G_i);
	}

	if(searcher.get_covered() == p) return true;
	return false;
}

void KCO::run() {
	//double lower = 1;
	//double upper = searcher.lower_bound();
	//searcher.construct_disks();
	cover();
	//searcher.new_raduis(r);
}
