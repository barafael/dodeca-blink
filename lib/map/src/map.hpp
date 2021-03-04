#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef>

template<typename K, typename V, size_t SIZE>
class Map {
  public:
    void reset() {
      len = 0;
    }

    V *get(K key) {
        for (size_t i = 0; i < SIZE; i++) {
            if (keys[i] == key) {
                return &values[i];
            }
        }
        return nullptr;
    }

    bool set(K key, V value) {
      if (len >= SIZE) {
        return false;
      }

      bool present = false;
      for (size_t i = 0; i < SIZE; i++) {
        if (keys[i] == key) {
          values[i] = value;
          return true;
        }
      }
      keys[len] = key;
      values[len] = value;
      len++;
      return true;
    }

    size_t get_len() {
        return len;
    }

  private:
    size_t len = 0;
    K keys[SIZE];
    V values[SIZE];
};

#endif// MAP_HPP