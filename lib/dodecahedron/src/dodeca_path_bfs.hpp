#ifndef DODECA_PATH_BFS_HPP
#define DODECA_PATH_BFS_HPP

#include <cstddef>
#include <cstdint>

#include "dodeca_path_calc.hpp"
#include "dodecahedron.hpp"

#include "map.hpp"
#include "queue.hpp"

class NodeDistancePair {
  public:
    NodeDistancePair() = default;
    NodeDistancePair(size_t node_index, size_t distance): node_index(node_index), distance(distance) { }
    size_t get_node() { return node_index; }
    size_t get_dist() { return distance; }

  private:
    size_t node_index = 0;
    size_t distance = 0;
};

class DodecaPathBFS: public PathCalculator {
  public:
  DodecaPathBFS(Dodecahedron* dod): dod(dod) {}
    Path get_path(size_t from_node_index, size_t to_node_index) override {
      Map<size_t, size_t, 32> previous;
      Queue<NodeDistancePair, 32> queue;

      NodeDistancePair start(from_node_index, 0);
      queue.push(start);

      while (queue.len() > 0) {
        NodeDistancePair pair = queue.pop();
        if (pair.get_node() == to_node_index) {
          Path result;
          size_t current_node = pair.get_node();
          result.append(current_node);
          while(current_node != from_node_index) {
            size_t previous_node = *previous.get(current_node);
            result.append(previous_node);
            current_node = previous_node;
          }
          return result;
        }

        Neighbours n = dod->get_neighbouring_nodes_of(pair.get_node());
        for (size_t i = 0; i < 3; i++) {
          if (!previous.has_key(n[i])) {
            previous.set(n[i], pair.get_node());
            NodeDistancePair p(n[i], pair.get_dist() + 1);
            queue.push(p);
          }
        }
      }
      // Only possible if error before.
      Path impossible;
      return impossible;
    }

    private:
      Dodecahedron *dod;
};

#endif// DODECA_PATH_BFS_HPP