#pragma once
#include <filesystem>
#include <functional>

std::size_t hashRawBytes(const std::filesystem::path& path);

void forEveryFileInPathDo(const std::filesystem::path& dirToSearch, std::function<void(std::filesystem::directory_entry)> doForFile);
