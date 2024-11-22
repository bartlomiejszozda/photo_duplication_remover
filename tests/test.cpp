#include <gtest/gtest.h>
#include "DuplicationFinder.h"

TEST(Test, getUniqueFiles){
    std::filesystem::path dirToSearchPath = "../test_data";
    const auto& uniqueFiles = DuplicationFinder::findDuplications(dirToSearchPath);
    EXPECT_EQ(6, uniqueFiles.size());
}