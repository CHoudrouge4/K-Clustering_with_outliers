#pragma once
#include <vector>
#include <string>
#include <limits>
#include <map>
#include <unordered_map>
#include <set>
#include "grid.h"

template <typename T>
struct cmp {
	bool operator()(const T& lhs, const T& rhs) { return lhs > rhs; }
};

class FRS : public grid {
private:
	int covered = 0; // number of covored points so far
	double radius;
	double radius_2;
	vec_int disks_sizes;
	std::vector<vec_pair> G; // the G disks
	std::vector<vec_pair> E; // the E disks
	std::vector<vec_int> point_to_disks; // the disks of a given point
	std::set<std::pair<int, int>, cmp<std::pair<int, int>>> disks; // priotity queue of the heaviest disks
	std::unordered_map<std::pair<int, int>, vec_int, pairhash> cell_to_disk; // the disks for which a cell belongs

	/**
	* Computes the distance square
	*/
	double distance_2(const int p, const int q) const;

	/**
	* marks the disks as covered
	*/
	void mark_corresponding_disk(std::pair<int, int> &p);

	/**
	* initializes the fields
	*/
	void init();
public:
	FRS(const std::string file_name, const double r);
	FRS(const std::string file_name, const double r, int nb_pts);

	/**
	* Construct the disks
	*/
	void construct_disks();

	/**
	* Update the disks in term of sizes and covered points
	*/
	void update_disks(std::pair<int, int> disk);

	/**
	* Return the heaviest disk
	*/
	std::pair<int, int> get_heaviest_disk();

	/**
	* Changes the raduis and apply the affected changes
	*/
	void new_raduis(const double);

	/**
	* Returns the cumber of covered cells
	*/
	int get_covered();

	/**
	* Returns a lower upper bound on r
	*/
	double upper_bound();

	/**
	* Returns the stored points
	*/
	const std::vector<double>& get_points();

	/**
	* Returns the number of stored points
	*/
	const int& data_size();

	/**
	* Returns the points in a given disk id
	*/
	vec_pts get_g_points(const int id);
};
