#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "Differentiators.h"
#include "DuplicationCandidatesFinder.h"

template <typename T>
void printVecVec(std::vector<std::vector<T>> vec){
    std::cout << "print vecvec\n";
    for (auto &els: vec){
        for (auto &similar : els) {
            std::cout << similar << "\n";
        }
        std::cout << std::endl;
    }
}

// Convert a value to string using stream operator<<
template <typename T>
static std::string toString(const T &value){
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Escape CSV field: double quotes and wrap in quotes if contains comma, quote or newline
static std::string escapeCsvField(const std::string &field){
    bool needQuotes = false;
    for (char c : field) {
        if (c == '"' || c == ',' || c == '\n' || c == '\r') { needQuotes = true; break; }
    }
    std::string out;
    out.reserve(field.size() + 2);
    if (needQuotes) out.push_back('"');
    for (char c : field){
        if (c == '"') out.append("\""); // double the quote
        out.push_back(c);
    }
    if (needQuotes) out.push_back('"');
    return out;
}

// Write nested vector to CSV file. Fields are escaped per CSV rules (quotes doubled, fields with comma/newline/quote are quoted).
template <typename T>
void writeVecVecCsv(const std::vector<std::vector<T>> &vec, const std::filesystem::path &outPath){
    std::ofstream ofs(outPath);
    if (!ofs.is_open()){
        std::cerr << "Failed to open file for writing: " << outPath << std::endl;
        return;
    }

    for (const auto &row : vec){
        bool first = true;
        for (const auto &cell : row){
            if (!first) ofs << ',';
            first = false;
            std::string s = toString(cell);
            ofs << escapeCsvField(s);
        }
        ofs << '\n';
    }

    ofs.flush();
}

int main(){
    std::filesystem::path dirToSearchPath = "/container/camera_read_only";

    std::cout << "list all files" << std::endl; 
    auto filter = FilesFilter{dirToSearchPath};

    std::cout << "filtered by name" << std::endl; 
    auto result = filter.filter<FileName>().getLastResult();
    // printVecVec(result);

    std::cout << "filtered by size" << std::endl; 
    result = filter.filter<FileSize>().getLastResult();
    writeVecVecCsv(result, "/tmp/duplicates.csv");
    // printVecVec(result);

    // std::cout << "filtered by hash" << std::endl; 
    // result = filter.filter<FileHash>().getLastResult();
    // printVecVec(result);
    return 0;
}