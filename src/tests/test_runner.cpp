#include "gtest/gtest.h"

int main() {
    testing::InitGoogleTest();
    std::cout << RUN_ALL_TESTS() << " TESTS FAILED!" << std::endl;
}
