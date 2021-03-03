#ifndef DODECA_GRAPH_HPP
#define DODECA_GRAPH_HPP

#include <cstddef>

class Node {
  public:
    size_t edge_index[3];
};

class Edge {
  public:
    size_t node_index[2];
};

#endif// DODECA_GRAPH_HPP