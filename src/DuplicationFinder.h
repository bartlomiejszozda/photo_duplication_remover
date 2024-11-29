#pragma once
#include <vector>
#include <filesystem>
#include <iostream>

#include "DuplicatedFiles.h"

void forEveryFileInPathDo(const std::filesystem::path& dirToSearch, auto doForFile){
    namespace fs = std::filesystem;
    try{
        for (const fs::directory_entry& entry : fs::recursive_directory_iterator(dirToSearch)){
            if (fs::is_regular_file(entry) && fs::exists(entry.path())){
                doForFile(entry);
            }
        }
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

class DuplicationFinder{
public:
    [[nodiscard]] static DuplicatedFiles findUniqueFiles(const std::filesystem::path& dirToSearch){
        DuplicatedFiles files;
        auto addFile = [&](const auto& entry){
          files.newPath(entry.path());
        };
        forEveryFileInPathDo(dirToSearch, addFile);
        return files;
    }
};