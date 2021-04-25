#pragma once

#include "dodeca_node.hpp"
#include "dodeca_edge.hpp"

#include <array>
#include <cstddef>

enum class TraverseType : size_t
{
    TO        = 0,
    FROM      = 1,
    SNOWFLAKE = 2,
};

constexpr size_t NUM_NODES = 20;
constexpr size_t NUM_EDGES = 30;

class Dodecahedron {
    public:
        Dodecahedron() = default;

        std::array<size_t, 3> get_neighbouring_nodes_of(size_t node_index) const {
            return std::array<size_t, 3> {
                edges[nodes[node_index].edge_index[0]].traverse_from(node_index),
                edges[nodes[node_index].edge_index[1]].traverse_from(node_index),
                edges[nodes[node_index].edge_index[2]].traverse_from(node_index),
            };
        }

        std::array<Node, NUM_NODES> nodes {{
            Node {5, 0, 1},
            Node {6, 1, 2},
            Node {7, 2, 3},
            Node {8, 3, 4},
            Node {9, 4, 0},
            Node {19, 5, 10},
            Node {15, 6, 11},
            Node {16, 7, 12},
            Node {17, 8, 13},
            Node {18, 9, 14},
            Node {20, 15, 10},
            Node {21, 16, 11},
            Node {22, 17, 12},
            Node {23, 18, 13},
            Node {24, 19, 14},
            Node {25, 20, 29},
            Node {26, 21, 25},
            Node {27, 22, 26},
            Node {28, 23, 27},
            Node {29, 24, 28},
        }};

        std::array<Edge, NUM_EDGES> edges {{
            Edge {4, 0},
            Edge {0, 1},
            Edge {1, 2},
            Edge {2, 3},
            Edge {3, 4},
            Edge {0, 5},
            Edge {1, 6},
            Edge {2, 7},
            Edge {3, 8},
            Edge {4, 9},
            Edge {5, 10},
            Edge {6, 11},
            Edge {7, 12},
            Edge {8, 13},
            Edge {9, 14},
            Edge {6, 10},
            Edge {7, 11},
            Edge {8, 12},
            Edge {9, 13},
            Edge {5, 14},
            Edge {10, 15},
            Edge {11, 16},
            Edge {12, 17},
            Edge {13, 18},
            Edge {14, 19},
            Edge {15, 16},
            Edge {16, 17},
            Edge {17, 18},
            Edge {18, 19},
            Edge {19, 15},
        }};
};
