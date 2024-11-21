#include <gtest/gtest.h>
#include <filesystem>
#include "include/DuplicationFinder"

TEST(Test, listAllFiles){
    auto duplication_finder = DuplicationFinder{};
    const auto& files = duplication_finder.listAllFiles();
    EXPECT(files.size() == 5);
}