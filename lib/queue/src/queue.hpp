#pragma once

#include <cstddef>
#include <array>

template<typename T, size_t SIZE>
class Queue {
public:
    constexpr Queue(): oldest(), num_elems(), data() {}

    constexpr void push(T elem) {
        size_t index = (oldest + num_elems) % SIZE;
        data[index] = elem;
        if (num_elems == SIZE) {
            oldest = (oldest + 1) % SIZE;
        } else {
            num_elems++;
        }
    }

    constexpr T pop() {
        T elem = data[oldest];
        oldest = (oldest + 1) % SIZE;
        num_elems--;
        return elem;
    }

    constexpr T *peek() {
        if (is_empty()) {
            return nullptr;
        }
        return &data[oldest];
    }

    constexpr size_t len() const {
        return num_elems;
    }

    constexpr bool is_empty() const {
        return len() == 0;
    }

    constexpr bool is_full() {
        return len() == SIZE;
    }

private:
    size_t oldest = 0;
    size_t num_elems = 0;
    std::array<T, SIZE> data = {};
};