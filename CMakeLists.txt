cmake_minimum_required(VERSION 3.0)
project(photo_duplication_remover)

set(CMAKE_CXX_STANDARD 23)

add_executable(main_duplication_remover src/main.cpp)

#GTEST START
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_duplication_remover tests/test.cpp)

target_include_directories(
        test_duplication_remover
        PRIVATE
        include
        )

target_link_libraries(
        test_duplication_remover
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_duplication_remover)
#GTEST END
