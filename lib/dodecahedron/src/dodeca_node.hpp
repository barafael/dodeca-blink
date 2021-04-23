#pragma once

#include <array>
#include <cstddef>

class Node {
  public:
    constexpr Node() = default;
    constexpr Node(size_t index1, size_t index2, size_t index3): edge_index {index1, index2, index3} {};

    std::array<size_t, 3> edge_index = {};
};
