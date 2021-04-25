#pragma once

#include <array>
#include <cstddef>

class Edge {
  public:
    Edge() = default;
    Edge(size_t index1, size_t index2): node_index {index1, index2} {};

    size_t traverse_from(size_t node) const {
        if (node_index[0] == node) {
            return node_index[1];
        }
        if (node_index[1] == node) {
            return node_index[0];
        }
        return invalid_node;
    }

    const size_t invalid_node = 0xFFFFFFFF;

    std::array<size_t, 2> node_index {};
};
