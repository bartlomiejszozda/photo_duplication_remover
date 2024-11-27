#include <filesystem>
#include <unordered_map>

#include <DuplicatedFile.h>
#include <ranges>

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

template <typename Differentiator>
requires Hashable<Differentiator> && ConstructibleFromPath<Differentiator> && Comparable<Differentiator>
class DuplicatedFiles {
public:
    void newPath(const std::filesystem::path& path){
        try{
            duplicatedFiles.at(Differentiator{path}).addDuplication(path);
        }
        catch(const std::out_of_range& e){
            duplicatedFiles.insert({Differentiator{path}, DuplicatedFile{path}});
        }
    }
    [[nodiscard]] size_t size() const{
        return duplicatedFiles.size();
    }
private:
    std::unordered_map<Differentiator, DuplicatedFile> duplicatedFiles;
};
