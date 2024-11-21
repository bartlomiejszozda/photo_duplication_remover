#pragma once
#include <vector>
#include <filesystem>

class DuplicationFinder{
public:
    std::vector<std::filesystem::path> listAllFiles();
};