#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <ranges>

#include <helpers.h>

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


class FilesFilter{
    using SimilarFiles = std::vector<std::filesystem::path>;
public:
    explicit FilesFilter(const std::filesystem::path &dirToSearch){
        listAllFiles(dirToSearch);
    }
    const std::vector<SimilarFiles>& getLastResult() const{
        return lastResult;
    }

    template <typename Differentiator>
    requires Hashable<Differentiator> && ConstructibleFromPath<Differentiator> && Comparable<Differentiator>
    FilesFilter&filter() {
        lastResult = findSimilarFiles<Differentiator>();
        return *this;
    }

private:
    template<typename Differentiator>
    [[nodiscard]] std::vector<SimilarFiles> findSimilarFiles() const {
        auto filter = [](const SimilarFiles& similarFiles){
          std::unordered_map<Differentiator, SimilarFiles> groupsOfSimilarFiles;
          for (auto& path: similarFiles) {
              Differentiator differentiator{path};
              auto search = groupsOfSimilarFiles.find(differentiator);
              if(search != groupsOfSimilarFiles.end()){
                  search->second.emplace_back(std::move(path));
              }
              else{
                  groupsOfSimilarFiles.emplace(std::move(differentiator), SimilarFiles{std::move(path)});
              }
          }
          return groupsOfSimilarFiles;
        };
        std::vector<SimilarFiles> tmp;
        for (const auto& paths: lastResult){
            auto filtered = filter(paths);
            for (auto& similarFiles : filtered){
                if(similarFiles.second.size() > 1){
                    tmp.emplace_back(std::move(similarFiles.second));
                }
            }
        }
        return tmp;
    }

    void listAllFiles(const std::filesystem::path &dirToSearch) {
        auto addFile = [this](const std::filesystem::directory_entry& entry){
            lastResult.at(0).emplace_back(entry.path());
        };
        forEveryFileInPathDo(dirToSearch, addFile);
    }

    std::vector<SimilarFiles> lastResult{{}};
};
