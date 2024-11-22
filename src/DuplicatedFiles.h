#include <filesystem>

#include <unordered_map>

#include "DuplicatedFile.h"

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

class DuplicatedFiles {
public:
    void newPath(const std::filesystem::path& path);
    [[nodiscard]] size_t size() const;
private:
    std::unordered_map<FileNameSize, DuplicatedFile> duplicatedFiles;

};