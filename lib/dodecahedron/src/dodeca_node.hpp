#pragma once

#include <array>
#include <cstddef>

class Node {
  public:
    Node() = default;
    Node(size_t index1, size_t index2, size_t index3): edge_index {index1, index2, index3} {};

    std::array<size_t, 3> edge_index = {};
};
