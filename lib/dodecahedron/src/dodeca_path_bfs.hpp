#ifndef DODECA_PATH_BFS_HPP
#define DODECA_PATH_BFS_HPP

#include <cstddef>
#include <cstdint>

#include "dodeca_path_calc.hpp"
#include "dodecahedron.hpp"
#include "map.hpp"
#include "queue.hpp"

class DodecaPathBFS: public PathCalculator {
    Path get_path(size_t from_node_index, size_t to_node_index) override {
      Map<size_t, size_t, 32> previous;
      Queue<size_t, 16> queue;
    }
};

class NodeDistancePair {
  public:
    NodeDistancePair(size_t node_index, size_t distance): node_index(node_index), distance(distance) { }

  private:
    size_t node_index;
    size_t distance;
};

class Path {
  public:
    bool contains(size_t index) {
        for (size_t i = 0; i < num_elems; i++) {
            if (nodes[i] == index) {
                return true;
            }
        }
        return false;
    }

    void append(size_t index) {
        if (!contains(index)) {
            if (num_elems < MAX_PATH_LEN - 1) {
                nodes[num_elems] = index;
                num_elems++;
            }
        }
    }

    void reset() {
        num_elems = 0;
    }

  private:
    size_t num_elems           = 0;
    size_t nodes[MAX_PATH_LEN] = {};
};

#endif// DODECA_PATH_BFS_HPP