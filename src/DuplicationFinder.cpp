#include "DuplicationFinder.h"

#include <iostream>

DuplicatedFiles DuplicationFinder::findDuplications(const std::filesystem::path& dirToSearch){
    namespace fs = std::filesystem;
    DuplicatedFiles files;
    try{
        for (const auto& entry : fs::recursive_directory_iterator(dirToSearch)){
            if (fs::is_regular_file(entry) && fs::exists(entry.path())){
                files.newPath(entry.path());
            }
        }
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return files;
}