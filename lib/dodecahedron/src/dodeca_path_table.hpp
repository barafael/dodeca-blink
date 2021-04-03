#pragma once

#include <cstddef>
#include <cstdint>

#include "dodeca_path_calc.hpp"
#include "dodecahedron.hpp"
#include "dodeca_path_bfs.hpp"

class DodecaPathTable : public PathCalculator {
public:
    Path get_path(size_t from_node_index, size_t to_node_index) override {
        return table[from_node_index][to_node_index];
    }


private:
    Path table[NUM_NODES][NUM_NODES] = {};
};