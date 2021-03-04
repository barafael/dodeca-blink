#ifndef DODECA_PATH_CALC_HPP
#define DODECA_PATH_CALC_HPP

#include <cstddef>

#include "dodeca_graph.hpp"

constexpr size_t MAX_PATH_LEN = 5;

class Path {
  public:
    size_t nodes[MAX_PATH_LEN] = {};
    size_t len = 0;
};

class PathCalculator {
    virtual Path get_path(size_t from_node_index, size_t to_node_index) = 0;
};

#endif// DODECA_PATH_CALC_HPP