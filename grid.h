#pragma once
#include <unordered_map>
#include <limits>
#include <vector>

typedef std::vector<double> point;
typedef std::vector<int> vec_int;
typedef std::vector<point> vec_pts;
typedef std::vector<bool> vec_bool;
typedef std::vector<std::pair<int, int>> vec_pair;

/**
* Hash function for the pair of integers.
*/
struct pairhash {
private:
  const std::size_t num = 65537;
public:
  std::size_t operator()(const std::pair<int, int> &x) const {
    return (x.first * num) ^ x.second;
  }
};

struct grid {
public:
  bool given = false; //  true if the number of points is specified, false otherwize (number of points = 1000000).
  std::unordered_map<std::pair<int, int>, vec_int, pairhash> mp;
  double min_x = std::numeric_limits<double>::max(); // minimum x coordinates
  double max_x = std::numeric_limits<double>::min(); // maximum x coordinates
  double min_y = min_x; // min y coordinates
  double max_y = max_x; // max y coordinates
  double radius;
  double radius_2;
  int dimension;
  int number_points;

  // store the data points x_0,y_0, x_1,y_1 .......
  std::vector<double> points;

  /**
  * builds the grid
  */
  void build();

  /**
  * Read the points from a given file name
  */
  void read_points(const std::string file_name);

  /**
  * Returns the i index of a point p in the grid.
  */
  int get_i_index(const size_t p) const;

  /**
  * Returns the j index of a point p in the grid.
  */
  int get_j_index(const size_t p) const;

  grid(){};
  grid(const std::string file_name, const double r);
  grid(const std::string file_name, const double r, int nb_pts);

  /**
  * Builds the grid with a new radius r
  */
  void reset(const double r);

  /**
  * Returns the indices of the points in a given cell.
  */
  const vec_int& get_cell_points(const size_t, const size_t);
};
