#pragma once

#include "dodeca_node.hpp"

#include <array>
#include <cstddef>

enum class TraversalDirection : size_t {
    UP   = 0,
    DOWN = 1,
};

constexpr size_t NUM_NODES = 20;
constexpr size_t NUM_EDGES = 30;

class Dodecahedron {
    public:
    Dodecahedron() = default;

    Node get_node(node_index index) {
        return nodes[index];
    }

    private:
    std::array<Node, NUM_NODES> nodes {
        { Node { 1, 5, 4 },    Node { 0, 2, 6 },    Node { 1, 3, 7 },    Node { 2, 4, 8 },    Node { 0, 3, 9 },
          Node { 0, 10, 14 },  Node { 1, 10, 11 },  Node { 2, 11, 12 },  Node { 3, 12, 13 },  Node { 4, 13, 14 },
          Node { 5, 6, 15 },   Node { 6, 7, 16 },   Node { 7, 8, 17 },   Node { 8, 9, 18 },   Node { 5, 9, 19 },
          Node { 10, 16, 19 }, Node { 11, 15, 17 }, Node { 12, 16, 18 }, Node { 13, 17, 19 }, Node { 14, 15, 18 } }
    };
};
