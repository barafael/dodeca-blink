#ifndef DODECA_PATH_TABLE_HPP
#define DODECA_PATH_TABLE_HPP

#include "dodeca_path_calc.hpp"
#include "dodecahedron.hpp"

class DodecaPathTable: public PathCalculator {
    Path get_path(size_t from_node_index, size_t to_node_index) override {
        return table[from_node_index][to_node_index];
    }

  private:
    Path table[NUM_NODES][NUM_NODES] = {};
};

#endif// DODECA_PATH_TABLE_HPP