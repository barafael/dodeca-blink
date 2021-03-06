#include "queue.hpp"

#include <unity.h>

namespace Test_NativeQueue {

    void test_push() {
        Queue<int, 4> q;
        TEST_ASSERT(q.is_empty());
        TEST_ASSERT(q.len() == 0);

        q.push(3);
        q.push(4);

        TEST_ASSERT(q.len() == 2);

        TEST_ASSERT(q.pop() == 3);
        TEST_ASSERT(q.pop() == 4);
        TEST_ASSERT(q.peek() == nullptr);
        TEST_ASSERT(q.len() == 0);
        TEST_ASSERT(q.is_empty());
    }

    void test_queue_push_overwrite() {
        Queue<int, 4> q;

        q.push(8);
        TEST_ASSERT(*q.peek() == 8);
        TEST_ASSERT(q.len() == 1);

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

        TEST_ASSERT(q.is_full());

        TEST_ASSERT(q.len() == 4);
        TEST_ASSERT(q.pop() == 4);
        TEST_ASSERT(q.len() == 3);

        TEST_ASSERT(*q.peek() == 5);
        TEST_ASSERT(q.pop() == 5);
        TEST_ASSERT(q.len() == 2);

        TEST_ASSERT(q.pop() == 6);
        TEST_ASSERT(q.len() == 1);

        TEST_ASSERT(q.pop() == 7);
        TEST_ASSERT(q.len() == 0);
        TEST_ASSERT(q.is_empty());
    }

    constexpr size_t const_queue_len_helper() {
        Queue<char, 8> q;
        q.push('a');
        q.push('g');
        q.push('x');
        return q.len();
    }

    constexpr uint32_t const_queue_pushpop() {
        Queue<uint32_t, 5> q;
        q.push(3);
        q.push(4);
        q.push(5);
        q.push(6);
        q.push(7);
        q.push(8);
        q.push(9);
        q.push(10);
        q.push(11);
        q.push(12);
        return q.pop();
    }

    constexpr bool constexpr_test_push_helper() {
        Queue<uint64_t, 4> q;
        if (!q.is_empty()) {
            TEST_ASSERT(false);
        }
        if (q.len() != 0) {
            TEST_ASSERT(false);
        }

        q.push(3);
        q.push(4);

        if (q.len() != 2) {
            TEST_ASSERT(false);
        }

        if (q.pop() != 3) {
            TEST_ASSERT(false);
        }
        if (q.pop() != 4) {
            TEST_ASSERT(false);
        }
        if (q.peek() != nullptr) {
            TEST_ASSERT(false);
        }
        if (q.len() != 0) {
            TEST_ASSERT(false);
        }
        if (!q.is_empty()) {
            TEST_ASSERT(false);
        }
        return true;
    }

    void test_queue_constexpr() {
        static_assert(const_queue_len_helper() == 3, "");
        static_assert(const_queue_pushpop() == 8, "");
        static_assert(constexpr_test_push_helper(), "");
    }

    void test_all() {
        UNITY_BEGIN();
        RUN_TEST(test_push);
        RUN_TEST(test_queue_push_overwrite);
        UNITY_END();
    }
}// namespace Test_NativeQueue