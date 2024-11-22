cmake_minimum_required(VERSION 3.28.3)
project(photo_duplication_remover)

set(CMAKE_CXX_STANDARD 23)

add_library(
sources
src/DuplicationFinder.cpp
src/DuplicatedFile.cpp
src/DuplicatedFile.h
src/DuplicatedFiles.cpp
src/DuplicatedFiles.h
)

target_include_directories(
        sources
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

add_executable(main_duplication_remover
src/main.cpp)

target_link_libraries(main_duplication_remover sources)

#GTEST START
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_duplication_remover
tests/test.cpp
src/DuplicationFinder.cpp)

target_link_libraries(
        test_duplication_remover
        sources
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_duplication_remover)
#GTEST END
