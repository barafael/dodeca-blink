#ifndef DODECAHEDRON_HPP
#define DODECAHEDRON_HPP

#include <cstddef>

#define NUM_NODES 20
#define NUM_EDGES 30

class Node {
  public:
    size_t edge_index[3];
};

class Edge {
  public:
    size_t node_index[2];
};

class Dodecahedron {
  public:
    Dodecahedron();
    //Path get_path(size_t from_node, size_t to_node);

  private:
    Node nodes[NUM_NODES];
    Edge edges[NUM_EDGES];
};

#endif // DODECAHEDRON_HPP
