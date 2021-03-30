#include "nodes.hpp"

namespace Test_NativeNodes {

void test_producer() {
    class Keyboard: public Producer<char> {
        public:
        char read() {
            static char c = 'a';
            return c++;
        }
    };

    Keyboard k;

    TEST_ASSERT(k.read() == 'a');
    TEST_ASSERT(k.read() == 'b');
    TEST_ASSERT(k.read() == 'c');
}

void test_all() {
    UNITY_BEGIN();
    RUN_TEST(test_producer);
    UNITY_END();
}
}// namespace Test_NativeNodes