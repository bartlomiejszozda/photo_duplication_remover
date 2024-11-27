#include <fstream>

struct FileNameSize {
    explicit FileNameSize(const std::filesystem::path& path):
            name(path.filename()), size(std::filesystem::file_size(path)){}
    bool operator==(const FileNameSize & other) const{
        return name == other.name && size == other.size;
    }
    const std::string name;
    const uint32_t size; // may not work with files bigger than ~4GB
};

namespace std {
    template <>
    struct hash<FileNameSize> {
        std::size_t operator()(const FileNameSize & obj) const {
            std::size_t hash1 = std::hash<std::string>{}(obj.name);
            std::size_t hash2 = std::hash<uint32_t>{}(obj.size);
            return hash1 ^ (hash2 << 1);  // Shift and XOR to combine
        }
    };
}

std::size_t hashRawBytes(const std::filesystem::path& path){
    std::ifstream file{path, std::ios::binary};
    if (!file){
        throw std::runtime_error("Failed to open file: " + path.string());
    }
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return std::hash<std::string_view>{}(std::string_view(buffer.data(), buffer.size()));
}

struct FileRawDataHash {
    explicit FileRawDataHash(const std::filesystem::path& path): name{path.filename()}, hash{hashRawBytes(path)}{}
    bool operator==(const FileRawDataHash & other) const {
        return name == other.name && hash == other.hash;
    }

    const std::string name;
    const size_t hash;
};

namespace std {
    template <>
    struct hash<FileRawDataHash> {
        std::size_t operator()(const FileRawDataHash & obj) const {
            return obj.hash;
        }
    };
}

