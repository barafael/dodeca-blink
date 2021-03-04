#include <unity.h>

#include "queue/test_native.hpp"
#include "dodecahedron/test_native.hpp"
#include "map/test_native.hpp"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void process() {
    Test_NativeQueue::test_all();
    Test_NativeDodecahedron::test_all();
    Test_NativeMap::test_all();
}

int main(int argc, char **argv) {
    process();
    return 0;
}