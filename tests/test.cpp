#include <gtest/gtest.h>
#include "DuplicationFinder.h"

TEST(Test, listAllFiles){
    auto duplication_finder = DuplicationFinder{};
    const auto& files = duplication_finder.listAllFiles();
    EXPECT_EQ(5, files.size());
}