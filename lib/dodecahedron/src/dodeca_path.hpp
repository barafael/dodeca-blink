#pragma once

#include <cstddef>
#include <cassert>

constexpr size_t MAX_PATH_LEN = 5;

using path_t = std::pair<std::array<size_t, MAX_PATH_LEN>, size_t>;

class Path {
  public:
    Path() = default;

    Path(std::initializer_list<size_t> list) {
        assert(list.size() <= MAX_PATH_LEN);
        num_elems = list.size();
        size_t i = 0;
        for (auto elem: list) {
            nodes[i++] = elem;
        }
    }

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

    const path_t get_data() const {
        return std::make_pair(nodes, num_elems);
    }

    const size_t len() const {
        return num_elems;
    }

    void reset() {
        num_elems = 0;
    }

    Path& operator=(const Path& other) {
        if (this == &other) {
            return *this;
        }
        this->num_elems = other.num_elems;
        for (size_t i = 0; i < other.num_elems; i++) {
            this->nodes[i] = other.nodes[i];
        }
        return *this;
    }

  private:
    size_t num_elems                       = 0;
    std::array<size_t, MAX_PATH_LEN> nodes = {};
};
