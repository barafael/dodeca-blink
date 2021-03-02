#ifndef DODECA_BFS_HPP
#define DODECA_BFS_HPP

#include <cstddef>
#include <cstdint>

#define PATH_LENGTH 16

class NodeDistancePair {
    public:
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
        if (num_elems < PATH_LENGTH - 1) {
          nodes[num_elems] = index;
          num_elems++;
        }
      }
    }

    void reset() {
      num_elems = 0;
    }

  private:
    size_t num_elems = 0;
    size_t nodes[PATH_LENGTH] = {};
};

#endif // DODECA_BFS_HPP