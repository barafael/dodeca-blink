#include "dodecahedron.hpp"
#include "dodeca_path_bfs.hpp"

#include "test_native.hpp"

namespace Test_NativeDodecahedron {

void test_short_path() {
    Dodecahedron dod;
    DodecaPathBFS bfs(&dod);

    Path p = bfs.get_path(0, 10);
    size_t len = 0;
    size_t *data = p.get_data(&len);
    TEST_ASSERT(len == 3);
    size_t expected[3] = {10, 5, 0};
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT(data[i] == expected[i]);
    }
}

void test_18_to_10() {
    Dodecahedron dod;
    DodecaPathBFS bfs(&dod);

    Path p = bfs.get_path(18, 10);
    size_t expected[4] = {10, 15, 19, 18};
    size_t len = 0;
    size_t *data = p.get_data(&len);
    TEST_ASSERT(len == 4);
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT(data[i] == expected[i]);
    }
}

void test_2_to_19() {
    Dodecahedron dod;
    DodecaPathBFS bfs(&dod);

    Path p = bfs.get_path(2, 19);
    size_t expected[5] = {19, 15, 16, 11, 7};
    size_t len = 0;
    size_t *data = p.get_data(&len);
    TEST_ASSERT(len == 5);
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT(data[i] == expected[i]);
    }
}

void test_9_to_17() {
    Dodecahedron dod;
    DodecaPathBFS bfs(&dod);

    Path p = bfs.get_path(9, 17);
    size_t expected[4] = {17, 18, 13, 9};
    size_t len = 0;
    size_t *data = p.get_data(&len);
    TEST_ASSERT(len == 4);
    for (size_t i = 0; i < len; i++) {
        TEST_ASSERT(data[i] == expected[i]);
    }
}

void test_navigate_graph() {
    Dodecahedron dod;
}

void test_all() {
    UNITY_BEGIN();
    RUN_TEST(test_short_path);
    RUN_TEST(test_18_to_10);
    RUN_TEST(test_2_to_19);
    RUN_TEST(test_9_to_17);
    RUN_TEST(test_navigate_graph);
    UNITY_END();
}
}// namespace Test_NativeQueue