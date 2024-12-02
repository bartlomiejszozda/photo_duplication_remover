#pragma once
#include <filesystem>
#include "helpers.h"


struct FileName{
    explicit FileName(const std::filesystem::path& path_):
            name{path_.filename()}{}
    bool operator==(const FileName& other) const{
        return name == other.name;
    }
    [[nodiscard]] std::size_t hash() const;
private:
    std::string name;
};

namespace std {
    template <>
    struct hash<FileName> {
        std::size_t operator()(const FileName& obj) const {
            return obj.hash();
        }
    };
}

struct FileSize {
    explicit FileSize(const std::filesystem::path& path_):
         size{std::filesystem::file_size(path_)}{}
    bool operator==(const FileSize & other) const{
        return size == other.size;
    }
    [[nodiscard]] std::size_t hash() const;
private:
    uint64_t size;
};

namespace std {
    template <>
    struct hash<FileSize> {
        std::size_t operator()(const FileSize& obj) const {
            return obj.hash();
        }
    };
}

struct FileHash {
    explicit FileHash(const std::filesystem::path& path_):
                hash_{hashRawBytes(path_)}{}
    bool operator==(const FileHash & other) const{
        return hash_ == other.hash_;
    }
    [[nodiscard]] std::size_t hash() const;
private:
    size_t hash_;
};

namespace std {
    template <>
    struct hash<FileHash> {
        std::size_t operator()(const FileHash& obj) const {
            return obj.hash();
        }
    };
}

/*
struct FileBytes {
    explicit FileBytes(const std::filesystem::path& path_):
            hash_{hashRawBytes(path_)}{}
    bool operator==(const FileBytes & other) const{
        return hash_ == other.hash_;
    }
    [[nodiscard]] std::size_t hash() const;
private:
    size_t bytes;
};

namespace std {
    template <>
    struct hash<FileBytes> {
        std::size_t operator()(const FileBytes& obj) const {
            return obj.hash();
        }
    };
}
 */