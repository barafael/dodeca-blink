#pragma once

#include "does_things.hpp"

#include<array>

constexpr size_t DATA_SIZE = 16;

class DodecaState: public ThingDoer {
public:
    explicit DodecaState(String name) : name(name) {}

    virtual void advance() = 0;

    String *get_name() {
        return &name;
    }

    uint8_t *get_data() {
        return &data[0];
    }

    void set_data(uint8_t *data) {
        memcpy(this->data.data(), data, DATA_SIZE);
    }

    virtual ~DodecaState() = default;

private:
    String name;
    std::array<uint8_t, DATA_SIZE> data = {};
};
