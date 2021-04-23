#include "map.hpp"

#include <unity.h>

namespace Test_NativeMap {

    void test_getset() {
        Map<int, char, 8> m;
        m.set(0, 'a');
        m.set(1, 'b');
        m.set(2, 'c');
        m.set(3, 'd');
        m.set(4, 'e');

        TEST_ASSERT_EQUAL(*m.get(0), 'a');
        TEST_ASSERT_EQUAL(*m.get(1), 'b');
        TEST_ASSERT_EQUAL(*m.get(2), 'c');
        TEST_ASSERT_EQUAL(*m.get(3), 'd');
        TEST_ASSERT_EQUAL(*m.get(4), 'e');
        TEST_ASSERT(m.get(5) == nullptr);

        m.set(0, 'z');
        TEST_ASSERT_EQUAL(*m.get(0), 'z');

        TEST_ASSERT_EQUAL(m.get_len(), 5);
        m.reset();
        TEST_ASSERT_EQUAL(m.get_len(), 0);
    }

    constexpr size_t const_map_len_helper() {
        Map<uint32_t, size_t, 64> map;
        map.set(1, 4096);
        map.set(2, 42);
        return map.get_len();
    }

    void test_getset_constexpr() {
        static_assert(const_map_len_helper() == 2, "");
        TEST_ASSERT_EQUAL(const_map_len_helper(), 2);
    }

    void test_all() {
        UNITY_BEGIN();
        RUN_TEST(test_getset);
        RUN_TEST(test_getset_constexpr);
        UNITY_END();
    }
}// namespace Test_NativeMap