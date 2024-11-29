#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <ranges>

#include <DuplicatedFile.h>
#include <Differentiators.h>
#include <helpers.h>

/*
template<typename T>
concept Hashable = requires(T a)
{
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept ConstructibleFromPath = std::is_constructible_v<T, std::filesystem::path>;

template <typename T>
concept Comparable = requires(T a, T b){
    {a == b} -> std::convertible_to<bool>;
};

template <typename SoftDifferentiator>
requires Hashable<SoftDifferentiator> && ConstructibleFromPath<SoftDifferentiator> && Comparable<SoftDifferentiator>
        */

class DuplicatedFiles {
public:
    void newPath(const std::filesystem::path& path){
        if(isNotADuplication(path)){
            differentFiles.insert(InitialDifferentiator{path});
        }
        else{
            checkForDuplicationByHash(path);
        }
    }

    bool isNotADuplication(const std::filesystem::path& path){
        auto search = differentFiles.find(InitialDifferentiator{path});
        return search == differentFiles.end();
    }
    void checkForDuplicationByHash(const std::filesystem::path& path){
        std::size_t hash = hashRawBytes(path);
        auto sameFile = duplicatedFiles.find(hash);
        if (sameFile == duplicatedFiles.end()){
            duplicatedFiles.insert({hash, {path}});
        }
        else{
            sameFile->second.emplace_back(path);
        }
    }

    [[nodiscard]] size_t size() const{
        return differentFiles.size();
    }
private:
    std::unordered_set<InitialDifferentiator> differentFiles;
    std::unordered_map<std::size_t, std::vector<std::filesystem::path>> duplicatedFiles;
};
