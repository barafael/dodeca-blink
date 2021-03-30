#pragma once

template<typename T>
class Producer {
  public:
    virtual T read() = 0;

    virtual ~Producer() = default;
};