#include "queue.hpp"

#include <iostream>
#include <cassert>

int main(void) {
    Queue<int, 4> q;
    assert(q.is_empty());

    q.push(3);
    q.push(4);

    assert(q.len() == 2);

    assert(q.pop() == 3);
    assert(q.pop() == 4);
    assert(q.peek() == nullptr);
    assert(q.len() == 0);
    assert(q.is_empty());

    q.push(1);
    assert(*q.peek() == 1);
    assert(q.len() == 1);

    q.push(4);
    q.push(3);
    q.push(2);
    q.push(1);
    q.push(4);
    q.push(0);
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(6);
    q.push(7);

    assert(q.is_full());

    assert(q.len() == 4);
    assert(q.pop() == 4);
    assert(q.len() == 3);

    assert(q.pop() == 5);
    assert(q.len() == 2);

    assert(q.pop() == 6);
    assert(q.len() == 1);

    assert(q.pop() == 7);
    assert(q.len() == 0);
    assert(q.is_empty());

    assert(q.is_empty());

    std::cout << "OK" << std::endl;
}