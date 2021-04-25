#pragma once

#include <cstddef>
#include <array>

template<typename K, typename V, size_t SIZE>
class Map {
  public:
    Map(): len(), keys(), values() {}

    void reset() {
        len = 0;
    }

    V *get(K key) {
        for (size_t i = 0; i < len; i++) {
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

        for (size_t i = 0; i < len; i++) {
            if (keys[i] == key) {
                values[i] = value;
                return true;
            }
        }
        keys[len] = key;
        values[len] = value;
        len += 1;
        return true;
    }

    bool has_key(K key) {
        for (size_t i = 0; i < len; i++) {
            if (key == keys[i]) {
                return true;
            }
        }
        return false;
    }

    size_t get_len() const {
        return len;
    }

private:
    size_t len = 0;
    std::array<K, SIZE> keys = {};
    std::array<V, SIZE> values = {};
};
