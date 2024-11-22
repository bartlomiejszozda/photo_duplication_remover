#pragma once
#include <vector>
#include <filesystem>

#include "DuplicatedFiles.h"

class DuplicationFinder{
public:
    [[nodiscard]] static DuplicatedFiles findDuplications(const std::filesystem::path& dirToSearch);
};