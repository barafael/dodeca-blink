#pragma once

#include <cstddef>

class NodeDistancePair {
  public:
    constexpr NodeDistancePair() = default;

    constexpr NodeDistancePair(size_t node_index, size_t distance): node_index(node_index), distance(distance) {
    }

    constexpr size_t get_node() const {
        return node_index;
    }

    constexpr size_t get_distance() const {
        return distance;
    }

  private:
    size_t node_index = 0;
    size_t distance   = 0;
};