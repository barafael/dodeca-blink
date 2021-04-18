#pragma once

#include <array>
#include <cstddef>

class Node {
  public:
    constexpr Node() = default;
    constexpr Node(size_t index1, size_t index2, size_t index3): edge_index{index1, index2, index3} {};

    std::array<size_t, 3> edge_index = {};
};

class Edge {
  public:
    constexpr Edge() = default;
    constexpr Edge(size_t index1, size_t index2): node_index {index1, index2} {};

    constexpr size_t traverse_from(size_t node) const {
        if (node_index[0] == node) {
            return node_index[1];
        }
        if (node_index[1] == node) {
            return node_index[0];
        }
        return invalid_node;
    }

    const size_t invalid_node = 0xFFFFFFFF;

    std::array<size_t, 2> node_index = {};
};
