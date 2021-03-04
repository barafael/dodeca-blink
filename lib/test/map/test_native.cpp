#include "map.hpp"

#include <unity.h>

namespace Test_NativeMap {

void test_getset() {
    Map<int, bool, 8> m;
    m.set(0, true);
    m.set(1, true);
    m.set(2, true);
    m.set(3, true);
    m.set(4, false);

    TEST_ASSERT(*m.get(0));
    TEST_ASSERT(*m.get(1));
    TEST_ASSERT(*m.get(2));
    TEST_ASSERT(*m.get(3));
    TEST_ASSERT(*m.get(4) == false);
    TEST_ASSERT(m.get(5) == nullptr);

    m.set(0, false);
    TEST_ASSERT(*m.get(0) == false);

    TEST_ASSERT(m.get_len() == 5);
    m.reset();
    TEST_ASSERT(m.get_len() == 0);
}

void test_all() {
    UNITY_BEGIN();
    RUN_TEST(test_getset);
    UNITY_END();
}
}// namespace Test_NativeMap