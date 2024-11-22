#include "DuplicatedFile.h"

#include <cassert>

DuplicatedFile::DuplicatedFile(const std::filesystem::path& first): paths{first}, name{first.filename()}{

}

void DuplicatedFile::addDuplication(const std::filesystem::path& duplication) {
    assert(duplication.filename() == name);
    paths.emplace_back(duplication);
}