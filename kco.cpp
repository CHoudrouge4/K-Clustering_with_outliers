#include "kco.h"

KCO::KCO(const std::string file_name, const int num_clusters) {
	FRS searcher = FRS(file_name, r);
	k = num_clusters;
}



void KCO::run() {
	searcher.construct_disks();  // O(n), O(n log n)
	for(int i = 0; i < k; ++i) {
		auto G_i = searcher.get_heaviest_disk(); //gi  O(log n)
		// mark Ei				   O(|Ei|)
		// updates all the disk    O()
	}
// if p is covered
}
