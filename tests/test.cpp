#include <gtest/gtest.h>
#include <filesystem>

TEST(Test, listAllFiles){
    auto duplication_finder = DuplicationFinder{};
    const auto& files = duplication_finder.listAllFiles();
    EXPECT(files.size() == 7);
}