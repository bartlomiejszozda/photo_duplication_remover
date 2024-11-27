#include <gtest/gtest.h>

#include "DuplicationFinder.h"
#include "Differentiators.h"

TEST(Test, getUniqueFilesBasedOnNameAndSize){
    std::filesystem::path dirToSearchPath = "../test_data";

    const auto& uniqueFiles = DuplicationFinder::findUniqueFiles<FileNameSize>(dirToSearchPath);
    EXPECT_EQ(6, uniqueFiles.size());
}

TEST(Test, getUniqueFilesBasedOnHash){
    std::filesystem::path dirToSearchPath = "../test_data";

    const auto& uniqueFiles = DuplicationFinder::findUniqueFiles<FileRawDataHash>(dirToSearchPath);
    EXPECT_EQ(6, uniqueFiles.size());
}

TEST (Test, sameHashWhenSameFiles){
    size_t hash1 = hashRawBytes("../test_data/dir1/1.png");
    size_t hash2 = hashRawBytes("../test_data/dir2/1.png");
    EXPECT_EQ(hash1, hash2);
}

TEST (Test, differentHashWhenDifferentFiles){
    size_t hash1 = hashRawBytes("../test_data/dir1/2.png");
    size_t hash2 = hashRawBytes("../test_data/dir2/1.png");
    EXPECT_NE(hash1, hash2);
}

TEST (Test, sameHashWhenSameFilesUnderDifferentNames){
    size_t hash1 = hashRawBytes("../test_data/dir1/3_but_different_name.png");
    size_t hash2 = hashRawBytes("../test_data/dir2/3.png");
    EXPECT_EQ(hash1, hash2);
}

