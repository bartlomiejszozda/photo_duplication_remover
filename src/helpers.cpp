#include "helpers.h"
#include <fstream>
#include <vector>

std::size_t hashRawBytes(const std::filesystem::path& path){
    std::ifstream file{path, std::ios::binary};
    if (!file){
        throw std::runtime_error("Failed to open file: " + path.string());
    }
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return std::hash<std::string_view>{}(std::string_view(buffer.data(), buffer.size()));
}
