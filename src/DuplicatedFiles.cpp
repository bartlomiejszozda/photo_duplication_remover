#include "DuplicatedFiles.h"
#include <ranges>

void DuplicatedFiles::newPath(const std::filesystem::path& path) {
    try{
        duplicatedFiles.at(FileNameSize{path}).addDuplication(path);
    }
    catch(const std::out_of_range& e){
        duplicatedFiles.insert({FileNameSize{path}, DuplicatedFile{path}});
    }
}

size_t DuplicatedFiles::size() const{
    return duplicatedFiles.size();
}
