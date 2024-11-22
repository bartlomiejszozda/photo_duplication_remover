#pragma once
#include <filesystem>
#include <vector>

class DuplicatedFile {
public:
    explicit DuplicatedFile(const std::filesystem::path& first);
    void addDuplication(const std::filesystem::path& duplication);
private:
    std::vector<std::filesystem::path> paths;
    const std::string name;
};


