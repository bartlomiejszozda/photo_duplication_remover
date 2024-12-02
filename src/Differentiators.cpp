#include "Differentiators.h"

std::size_t FileName::hash() const {
    return std::hash<std::string>{}(name);
}

std::size_t FileSize::hash() const {
    return std::hash<uint64_t>{}(size);
}

std::size_t FileHash::hash() const {
    return hash_;
}
