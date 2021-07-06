#pragma once

#include <cstddef>

class IndexPair {
    public:
    IndexPair() = default;

    IndexPair(size_t strip, size_t index) : strip(strip), index(index) {
    }

    size_t strip = 0;
    size_t index = 0;
};
