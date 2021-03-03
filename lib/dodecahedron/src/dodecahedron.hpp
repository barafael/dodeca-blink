#ifndef DODECAHEDRON_HPP
#define DODECAHEDRON_HPP

#include <cstddef>

#include "dodeca_cursor.hpp"
#include "dodeca_graph.hpp"

constexpr size_t NUM_NODES = 20;
constexpr size_t NUM_EDGES = 30;


class Dodecahedron {
  public:
    Dodecahedron();
    //Path get_path(size_t from_node, size_t to_node);

    DodecaNodeCursor get_cursor();
    DodecaNodeCursor get_cursor(size_t index);

    Node nodes[NUM_NODES];
    Edge edges[NUM_EDGES];
};

#endif// DODECAHEDRON_HPP
