#include "set.hpp"

#include <unity.h>

namespace Test_NativeSet {

void test_set() {
    Set<int, 8> set;
    TEST_ASSERT(set.get_len() == 0);
    TEST_ASSERT(set.contains(1) == false);
    TEST_ASSERT(set.put(4));
    TEST_ASSERT(set.put(5));
    TEST_ASSERT(set.contains(5));
    TEST_ASSERT(set.get_len() == 2);
}

void test_all() {
    UNITY_BEGIN();
    RUN_TEST(test_set);
    UNITY_END();
}
}// namespace Test_NativeSet