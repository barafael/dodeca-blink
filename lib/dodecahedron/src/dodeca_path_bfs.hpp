#pragma once

#include "dodeca_path.hpp"
#include "dodecahedron.hpp"
#include "map.hpp"
#include "queue.hpp"

#include <cstddef>
#include <cstdint>

#include <utility>

using node_distance_pair = std::pair<size_t, size_t>;

template<>
constexpr node_distance_pair& node_distance_pair::operator=(const node_distance_pair& other) {
    if (this == &other) {
        return *this;
    }
    this->first = other.first;
    this->second = other.second;
    return *this;
}

class DodecaPathBFS {
  public:
    constexpr DodecaPathBFS(): dod() { }

    constexpr Path get_path(size_t from_node_index, size_t to_node_index) {
        Map<size_t, size_t, 32> previous;
        Queue<std::pair<size_t, size_t>, 32> queue;

        node_distance_pair start(from_node_index, 0);
        queue.push(start);

        while (queue.len() > 0) {
            node_distance_pair pair = queue.pop();
            if (pair.first == to_node_index) {
                Path result;
                size_t current_node = pair.first;
                result.append(current_node);
                while (current_node != from_node_index) {
                    size_t previous_node = *previous.get(current_node);
                    result.append(previous_node);
                    current_node = previous_node;
                }
                return result;
            }

            std::array<size_t, 3> n = dod.get_neighbouring_nodes_of(pair.first);
            for (size_t i = 0; i < 3; i++) {
                if (!previous.has_key(n[i])) {
                    previous.set(n[i], pair.first);
                    node_distance_pair p(n[i], pair.second + 1);
                    queue.push(p);
                }
            }
        }
        // Only possible if error before.
        Path impossible;
        return impossible;
    }

  private:
    Dodecahedron dod;
};
