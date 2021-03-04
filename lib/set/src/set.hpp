#ifndef SET_HPP
#define SET_HPP

#include <cstddef>

template<typename T, size_t SIZE>
class Set {
  public:
    void reset() {
      len = 0;
    }

    bool contains(T elem) {
        for (size_t i = 0; i < SIZE; i++) {
            if (data[i] == elem) {
                return true;
            }
        }
        return false;
    }

    bool put(T elem) {
      if (len >= SIZE) {
        return false;
      }

      bool present = false;
      for (size_t i = 0; i < SIZE; i++) {
        if (data[i] == elem) {
          return false;
        }
      }
      data[len] = elem;
      len++;
      return true;
    }

    size_t get_len() {
        return len;
    }

  private:
    size_t len = 0;
    T data[SIZE];
};

#endif// SET_HPP