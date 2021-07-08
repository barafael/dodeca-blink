#pragma once

#include <cstddef>

class IndexPair {
    public:
    IndexPair() = default;

    IndexPair(size_t strip, size_t index) : pair(strip, index) {
    }

    size_t strip();
    size_t index();

    private:
    std::pair<size_t, size_t> pair;
};

size_t IndexPair::strip() {
    return pair.first;
}

size_t IndexPair::index() {
    return pair.second;
}
