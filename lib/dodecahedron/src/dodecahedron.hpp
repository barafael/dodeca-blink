#ifndef DODECAHEDRON_HPP
#define DODECAHEDRON_HPP

#include <cstddef>

#include "dodeca_graph.hpp"

constexpr size_t NUM_NODES = 20;
constexpr size_t NUM_EDGES = 30;


class Dodecahedron {
  public:
    Dodecahedron();

    Node nodes[NUM_NODES];
    Edge edges[NUM_EDGES];
};

#endif// DODECAHEDRON_HPP
