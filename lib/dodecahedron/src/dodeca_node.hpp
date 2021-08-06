#pragma once

#include <array>
#include <cstddef>

using node_index = size_t;

class Node {
    public:
    Node(node_index a, node_index b, node_index c) : a(a), b(b), c(c) {
    }

    std::array<node_index, 3> get_neighbours() {
        return std::array<node_index, 3> { a, b, c };
    }

    private:
    node_index a;
    node_index b;
    node_index c;
};
