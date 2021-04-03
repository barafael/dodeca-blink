#pragma once

#include <cstddef>
#include <array>

class Node {
public:
    std::array<size_t, 3> edge_index = {};
};

class Edge {
public:
    size_t traverse_from(size_t node) {
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
