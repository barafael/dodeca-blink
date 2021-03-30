#pragma once

#include <cstddef>
#include <array>

template<typename T, size_t SIZE>
class Queue {
  public:
    void push(T elem) {
      size_t index = (oldest + num_elems) % SIZE;
      data[index] = elem;
      if (num_elems == SIZE) {
        oldest = (oldest + 1) % SIZE;
      } else {
        num_elems++;
      }
    }

    T pop() {
      T elem = data[oldest];
      oldest = (oldest + 1) % SIZE;
      num_elems--;
      return elem;
    }

    T *peek() {
      if (is_empty()) {
        return nullptr;
      }
      return &data[oldest];
    }

    size_t len() {
      return num_elems;
    }

    bool is_empty() {
      return len() == 0;
    }

    bool is_full() {
      return len() == SIZE;
    }

  private:
    size_t oldest = 0;
    size_t num_elems   = 0;
    std::array<T, SIZE> data = {};
};