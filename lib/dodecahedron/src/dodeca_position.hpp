#pragma once

#include <cstddef>

class DodecaPosition {
    public:
    DodecaPosition(size_t edge_index, size_t percent): edge_index(edge_index), percent(percent) {}

    private:
    size_t edge_index = 0;
    size_t percent = 0;
};