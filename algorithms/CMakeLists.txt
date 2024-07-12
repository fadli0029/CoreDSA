cmake_minimum_required(VERSION 3.12)
project(DS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
find_package(Catch2 3 REQUIRED)

# Add dfs
add_executable(dfs_exe graph/dfs.cpp)
target_include_directories(dfs_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(dfs_exe Catch2::Catch2WithMain)
add_test(NAME DFSStackTest COMMAND dfs_exe)

# Add bfs
add_executable(bfs_exe graph/bfs.cpp)
target_include_directories(bfs_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(bfs_exe Catch2::Catch2WithMain)
add_test(NAME BFSTest COMMAND bfs_exe)
