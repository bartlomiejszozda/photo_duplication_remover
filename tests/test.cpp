#include "Differentiators.h"
#include "DuplicationCandidatesFinder.h"
#include <gtest/gtest.h>

template <typename T>
void printVecVec(std::vector<std::vector<T>> vec){
    std::cout << "print vecvec\n";
    for (auto &els: vec){
        for (auto &similar : els) {
            std::cout << similar << "\n";
        }
        std::cout << std::endl;
    }
}
TEST(Test, getUniqueFilesBasedOnNameAndSizeAndHash){
    std::filesystem::path dirToSearchPath = "../test_data";

    auto filter = FilesFilter{dirToSearchPath};
    const auto& result = filter.getLastResult();
    printVecVec(result);
    EXPECT_EQ(1, result.size());
    EXPECT_EQ(11, result[0].size());
    const auto& result2 = filter.filter<FileName>().getLastResult();
    printVecVec(result2);
    EXPECT_EQ(4, result2.size());
    const auto& result3 = filter.filter<FileSize>().getLastResult();
    printVecVec(result3);
    EXPECT_EQ(3, result3.size());
    const auto& result4 = filter.filter<FileHash>().getLastResult();
    printVecVec(result4);
    EXPECT_EQ(2, result4.size());
}

TEST(Test, useFilterCombinedCall){
    std::filesystem::path dirToSearchPath = "../test_data";

    auto result = FilesFilter{dirToSearchPath}.filter<FileName>().filter<FileSize>().filter<FileHash>().getLastResult();
    printVecVec(result);
    EXPECT_EQ(2, result.size());
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

TEST (Test, differentHashWhenSameNamesAndSizeButDifferentBytes){
    size_t hash1 = hashRawBytes("../test_data/dir2/5_pixel_changed.bmp");
    size_t hash2 = hashRawBytes("../test_data/dir3/5_pixel_changed.bmp");
    EXPECT_NE(hash1, hash2);
}
