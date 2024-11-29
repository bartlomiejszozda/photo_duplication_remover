#pragma once

struct InitialDifferentiator {
    explicit InitialDifferentiator(const std::filesystem::path& path):
            name{path.filename()}, size{std::filesystem::file_size(path)}{}
    bool operator==(const InitialDifferentiator & other) const{
        return name == other.name && size == other.size;
    }
    [[nodiscard]] std::size_t hash() const{
        std::size_t hashName = std::hash<std::string>{}(name);
        std::size_t hashSize = std::hash<uint64_t>{}(size);
        return hashName ^ (hashSize << 1);  // Shift and XOR to combine
    }
    const std::string name;
    const uint64_t size;
};

namespace std {
    template <>
    struct hash<InitialDifferentiator> {
        std::size_t operator()(const InitialDifferentiator & obj) const {
            return obj.hash();
        }
    };
}