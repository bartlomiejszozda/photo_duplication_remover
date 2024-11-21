#include "DuplicationFinder.h"

#include <iostream>

std::vector<std::filesystem::path> DuplicationFinder::listAllFiles(){
    namespace fs = std::filesystem;
    fs::path dirToSearchPath = "../test_data";
    std::vector<fs::path> files;
    try{
            for (const auto& entry : fs::recursive_directory_iterator(dirToSearchPath)){
                fs::file_status status = fs::status(entry);
                if (fs::is_regular_file(entry) && fs::exists(status)){
                    files.emplace_back(entry.path());
                }
            }
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return files;
}
