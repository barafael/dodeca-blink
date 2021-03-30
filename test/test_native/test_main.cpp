#include <unity.h>

#include "queue/test_native.hpp"
#include "dodecahedron/test_native.hpp"
#include "map/test_native.hpp"
#include "nodes/test_native.hpp"

int main(int argc, char **argv) {
    Test_NativeQueue::test_all();
    Test_NativeDodecahedron::test_all();
    Test_NativeMap::test_all();
    Test_NativeNodes::test_all();

    return 0;
}