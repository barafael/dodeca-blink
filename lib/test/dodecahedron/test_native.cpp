#include "dodecahedron.hpp"
#include "dodeca_path_bfs.hpp"

#include "test_native.hpp"

#include <utility>

namespace Test_NativeDodecahedron {

    void test_short_path() {
        DodecaPathBFS bfs;

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
        DodecaPathBFS bfs;

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
        DodecaPathBFS bfs;

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
        DodecaPathBFS bfs;

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

    void test_constexpr_edge() {
        constexpr Edge e1;
        constexpr Edge e2(1, 2);
        static_assert(e2.node_index[0] == 1, "constexpr construction of edge e2 failed");
        static_assert(e2.node_index[1] == 2, "constexpr construction of edge e2 failed");
    }

    void test_constexpr_edge_traverse() {
        constexpr Edge e(1, 2);
        constexpr size_t one = e.traverse_from(2);
        constexpr size_t two = e.traverse_from(1);
        static_assert(one == 1, "Wrong constexpr traversal");
        static_assert(two == 2, "Wrong constexpr traversal");

        static_assert(0xFFFFFFFF == e.traverse_from(3), "Wrong constexpr traversal");
    }

    void test_constexpr_node() {
        constexpr Node n2(4, 5, 6);
        static_assert(n2.edge_index[0] == 4, "constexpr construction of node n2 failed");
        static_assert(n2.edge_index[1] == 5, "constexpr construction of node n2 failed");
        static_assert(n2.edge_index[2] == 6, "constexpr construction of node n2 failed");
    }

    void test_constexpr_pair() {
        constexpr std::pair<size_t, size_t> p(4, 6);
        static_assert(p.first == 4, "constexpr construction of pair p failed");
        static_assert(p.second == 6, "constexpr construction of pair p failed");
    }

    void test_all() {
        UNITY_BEGIN();
        RUN_TEST(test_short_path);
        RUN_TEST(test_18_to_10);
        RUN_TEST(test_2_to_19);
        RUN_TEST(test_9_to_17);
        RUN_TEST(test_navigate_graph);
        RUN_TEST(test_constexpr_edge);
        RUN_TEST(test_constexpr_edge_traverse);
        RUN_TEST(test_constexpr_node);
        UNITY_END();
    }
}// namespace Test_NativeQueue