#pragma once

#include "dodeca_path_bfs.hpp"
#include "dodecahedron.hpp"

#include <cstddef>
#include <cstdint>

class DodecaPathTable {
  public:
    constexpr DodecaPathTable(): table() {
        DodecaPathBFS bfs;
        for (size_t from = 0; from < NUM_NODES; from++) {
            for (size_t to = 0; to < NUM_NODES; to++) {
                table[from][to] = bfs.get_path(from, to);
            }
        }
    }

    constexpr Path get_path(size_t from_node_index, size_t to_node_index) const {
        return table[from_node_index][to_node_index];
    }

  private:
    std::array<std::array<Path, NUM_NODES>, NUM_NODES> table = {};
};