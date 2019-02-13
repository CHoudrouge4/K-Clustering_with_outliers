#pragma once
#include <unordered_map>
#include <limits>
#include <vector>

typedef std::vector<double> point;
typedef std::vector<int> vec_int;
typedef std::vector<point> vec_pts;
typedef std::vector<bool> vec_bool;
typedef std::vector<std::pair<int, int>> vec_pair;

struct pairhash {
private:
  const std::size_t num = 65537;
public:
  std::size_t operator()(const std::pair<int, int> &x) const {
    return (x.first * num) ^ x.second;
  }
};

class grid {
public:
  std::unordered_map<std::pair<int, int>, vec_int, pairhash> mp;
  double min_x = std::numeric_limits<double>::max();
  double max_x = std::numeric_limits<double>::min();
  double min_y = min_x;
  double max_y = max_x;
  double radius;
  double radius_2;
  int dimension;

  std::vector<double> points;

  void build();
  void read_points(const std::string file_name);
  int get_i_index(const size_t p) const;
  int get_j_index(const size_t p) const;


  int number_points;
  grid(){};
  grid(const std::string file_name, const double r);
  void reset(const double r);
//  std::pair<int, int> get_cell(const size_t);
  const vec_int& get_cell_points(const size_t, const size_t);
  const vec_pts& get_points();
};
