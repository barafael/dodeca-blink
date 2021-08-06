#pragma once

#include "dodeca_path.hpp"
#include "dodecahedron.hpp"
#include "map.hpp"
#include "queue.hpp"

#include <cstddef>
#include <cstdint>

#include <utility>

using node_distance_pair = std::pair<node_index, size_t>;

class DodecaPathBFS {
    public:
    DodecaPathBFS() : dod() {
    }

    Node get_node(node_index index) {
        return dod.get_node(index);
    }

    Path get_path(node_index from, node_index to) {
        Map<node_index, node_index, 32> previous;

        Queue<std::pair<node_index, size_t>, 32> queue;

        node_distance_pair start(from, 0);
        queue.push(start);

        while (queue.len() > 0) {
            node_distance_pair pair = queue.pop();
            if (pair.first == to) {
                Path       result;
                node_index current_node = pair.first;
                result.append(current_node);
                while (current_node != from) {
                    node_index previous_node = *previous.get(current_node);
                    result.append(to);
                    current_node = previous_node;
                }
                return result;
            }

            std::array<node_index, 3> n = dod.get_node(pair.first).get_neighbours();
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
