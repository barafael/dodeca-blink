#pragma once

#include "dodeca_graph.hpp"

#include <cstddef>

constexpr size_t MAX_PATH_LEN = 5;

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
            if (num_elems < MAX_PATH_LEN) {
                nodes[num_elems] = index;
                num_elems++;
            }
        }
    }

    size_t *get_data(size_t *num_elems) {
        *num_elems = this->num_elems;
        return &nodes[0];
    }

    void reset() {
        num_elems = 0;
    }

  private:
    size_t num_elems           = 0;
    size_t nodes[MAX_PATH_LEN] = {};
};