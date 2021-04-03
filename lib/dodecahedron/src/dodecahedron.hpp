#pragma once

#include "dodeca_graph.hpp"

#include <array>
#include <cstddef>

constexpr size_t NUM_NODES = 20;
constexpr size_t NUM_EDGES = 30;

using Neighbours = std::array<size_t, 3>;

class Dodecahedron {
public:
    Dodecahedron();

    Neighbours get_neighbouring_nodes_of(size_t node_index);

    Node nodes[NUM_NODES];
    Edge edges[NUM_EDGES];
};
