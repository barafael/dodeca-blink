#ifndef DODECA_GRAPH_HPP
#define DODECA_GRAPH_HPP

#include <cstddef>

class Node {
  public:
    size_t edge_index[3];
};

class Edge {
  public:
    size_t traverse_from(size_t node) {
      if (node_index[0] == node) {
        return node_index[1];
      }
      if (node_index[1] == node) {
        return node_index[0];
      }
      return -1;
    }

    size_t node_index[2];
};

#endif// DODECA_GRAPH_HPP