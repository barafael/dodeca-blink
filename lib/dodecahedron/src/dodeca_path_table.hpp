#pragma once

#include "dodeca_path_bfs.hpp"
#include "dodecahedron.hpp"

#include <cstddef>
#include <cstdint>

class DodecaPathTable {
  public:
    Path get_path(size_t from_node_index, size_t to_node_index) {
        return table[from_node_index][to_node_index];
    }

  private:
    Path table[NUM_NODES][NUM_NODES] = {};
};