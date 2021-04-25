#include "dodecahedron.hpp"
#include "dodeca_path_bfs.hpp"
#include "dodeca_path_table.hpp"

#include "test_native.hpp"

#include <utility>

namespace Test_NativeDodecahedron {

    void test_short_path() {
        DodecaPathBFS bfs;

        Path p = bfs.get_path(0, 10);
        const path_t data = p.get_data();
        size_t len = p.len();
        TEST_ASSERT(len == 3);
        size_t expected[3] = {10, 5, 0};
        for (size_t i = 0; i < len; i++) {
            TEST_ASSERT(data.first[i] == expected[i]);
        }
    }

    void test_18_to_10() {
        DodecaPathBFS bfs;

        Path p = bfs.get_path(18, 10);
        size_t expected[4] = {10, 15, 19, 18};
        const path_t data = p.get_data();
        size_t len = p.len();
        TEST_ASSERT(len == 4);
        for (size_t i = 0; i < len; i++) {
            TEST_ASSERT(data.first[i] == expected[i]);
        }
    }

    void test_2_to_19() {
        DodecaPathBFS bfs;

        Path p = bfs.get_path(2, 19);
        size_t expected[5] = {19, 15, 16, 11, 7};
        const path_t data = p.get_data();
        size_t len = p.len();
        TEST_ASSERT(len == 5);
        for (size_t i = 0; i < len; i++) {
            TEST_ASSERT(data.first[i] == expected[i]);
        }
    }

    void test_9_to_17() {
        DodecaPathBFS bfs;

        Path p = bfs.get_path(9, 17);
        size_t expected[4] = {17, 18, 13, 9};
        const path_t data = p.get_data();
        size_t len = p.len();
        TEST_ASSERT(len == 4);
        for (size_t i = 0; i < len; i++) {
            TEST_ASSERT(data.first[i] == expected[i]);
        }
    }

    void test_navigate_graph() {
        Dodecahedron dod;
    }

    void test_make_table() {
        DodecaPathBFS bfs;
        DodecaPathTable table;
        for (size_t i = 0; i < NUM_NODES; i++) {
            for (size_t j = 0; j < NUM_NODES; j++) {
                auto expected = bfs.get_path(i, j);
                auto table_entry = table.get_path(i, j);
                TEST_ASSERT(expected.len() == table_entry.len());
                for (size_t i = 0; i < expected.len(); i++) {
                    TEST_ASSERT(expected.get_data().first[i] == table_entry.get_data().first[i]);
                }
            }
        }
    }

    void test_path() {
        Path p{3, 4, 5};
        size_t expected[3] = {3, 4, 5};
        TEST_ASSERT(p.len() == 3);
        for (size_t i = 0; i < 3; i++) {
            TEST_ASSERT(p.get_data().first[i] == expected[i]);
        }
    }

    void test_all() {
        UNITY_BEGIN();
        RUN_TEST(test_short_path);
        RUN_TEST(test_18_to_10);
        RUN_TEST(test_2_to_19);
        RUN_TEST(test_9_to_17);
        RUN_TEST(test_navigate_graph);
        RUN_TEST(test_make_table);
        RUN_TEST(test_path);
        UNITY_END();
    }
}// namespace Test_NativeQueue