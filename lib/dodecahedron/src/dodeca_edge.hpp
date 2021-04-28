#pragma once

#include <array>
#include <cstddef>

class Edge {
  public:
    Edge() = default;
    Edge(size_t index1, size_t index2): node_index {index1, index2} {};

    size_t traverse_from(size_t node) const {
        if (node_index.first == node) {
            return node_index.second;
        }
        if (node_index.second == node) {
            return node_index.first;
        }
        return invalid_node;
    }

    const size_t invalid_node = 0xFFFFFFFF;

    std::pair<size_t, size_t> node_index;
};
