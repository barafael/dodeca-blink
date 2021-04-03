#pragma once

#include "producer.hpp"

template<typename T>
class Consumer {
public:
    virtual void write(T value) = 0;

    virtual ~Consumer() = default;
};