#include "gtest/gtest.h"
#include "gmock/gmock.h"


int main(int argc, char* argv[]) {
    srand(time(NULL));
    testing::InitGoogleTest(&argc, argv);
    std::cout << "AEDA 2020/2021 - Practical 2 extra" << std::endl;
    return RUN_ALL_TESTS();
}