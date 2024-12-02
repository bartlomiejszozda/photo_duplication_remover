#include "helpers.h"

#include <fstream>
#include <iostream>
#include <vector>

std::size_t hashRawBytes(const std::filesystem::path& path){
    std::ifstream file{path, std::ios::binary};
    if (!file){
        throw std::runtime_error("Failed to open file: " + path.string());
    }
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return std::hash<std::string_view>{}(std::string_view(buffer.data(), buffer.size()));
}

void forEveryFileInPathDo(const std::filesystem::path &dirToSearch, std::function<void(std::filesystem::directory_entry)> doForFile) {
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
