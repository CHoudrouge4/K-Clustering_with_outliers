#include "kco.h"
#include <cmath>
KCO::KCO(const std::string file_name, const int num_clusters, const double alpha) {
	FRS searcher = FRS(file_name, r);
	k = num_clusters;
	p = std::ceil(1 - alpha) * searcher.get_points().size();
}

bool KCO::cover() {
	  // O(n), O(n log n)
	for(int i = 0; i < k; ++i) {
		auto G_i = searcher.get_heaviest_disk(); //gi  O(log n)
		// mark Ei				   O(|Ei|)
		// updates all the disk    O()
		searcher.update_disks(G_i);
	}

	if(searcher.get_covered() == p) return true;
	return false;
}

void KCO::run() {
	searcher.construct_disks();
	cover();
	searcher.new_raduis(r);
}
