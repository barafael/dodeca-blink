#ifndef DODECA_PATH_BFS_HPP
#define DODECA_PATH_BFS_HPP

#include <cstddef>
#include <cstdint>

#include "dodeca_path_calc.hpp"
#include "dodecahedron.hpp"

template<typename K, typename V, size_t SIZE>
class Map {
  public:
    void reset() {
      len = 0;
    }

    bool set(K key, V value) {
      if (len >= SIZE) {
        return false;
      }

      bool present = false;
      for (size_t i = 0; i < SIZE; i++) {
        if (keys[i] == key) {
          values[i] = value;
          return true;
        }
      }
      keys[len] = key;
      values[len] = value;
      len++;
    }

  private:
    size_t len = 0;
    K keys[SIZE];
    V values[SIZE];
};

class DodecaPathBFS: public PathCalculator {
    Path get_path(size_t from_node_index, size_t to_node_index) override {

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