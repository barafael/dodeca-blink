#include "dodecahedron.hpp"

#include <unity.h>

namespace Test_NativeDodecahedron {

void test_navigate_graph() {
    Dodecahedron dod;
}

void test_all() {
    UNITY_BEGIN();
    RUN_TEST(test_navigate_graph);
    UNITY_END();
}
}// namespace Test_NativeQueue