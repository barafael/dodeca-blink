#ifndef DODECA_CURSOR_HPP
#define DODECA_CURSOR_HPP

#include <cstddef>

#include "dodecahedron.hpp"
#include "dodeca_graph.hpp"

class DodecaNodeCursor {
  public:
    DodecaNodeCursor(Node *nodes, Edge *edges, size_t index):
    nodes(nodes),
    edges(edges),
    index(index) {}

  private:
    Node *nodes;
    Edge *edges;
    size_t index;
};

class DodecaEdgeCursor {
  public:
    DodecaEdgeCursor(Node *nodes, Edge *edges, size_t index):
    nodes(nodes),
    edges(edges),
    index(index) {}

  private:
    Node *nodes;
    Edge *edges;
    size_t index;
};

#endif// DODECA_CURSOR_HPP