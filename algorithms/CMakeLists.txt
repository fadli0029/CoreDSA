cmake_minimum_required(VERSION 3.12)
project(DS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
find_package(Catch2 3 REQUIRED)

# Add dfs_stack
add_executable(dfs_stack_exe graph/dfs_stack.cpp)
target_include_directories(dfs_stack_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(dfs_stack_exe Catch2::Catch2WithMain)
add_test(NAME DFSStackTest COMMAND dfs_stack_exe)

# Add bfs
add_executable(bfs_exe graph/bfs.cpp)
target_include_directories(bfs_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(bfs_exe Catch2::Catch2WithMain)
add_test(NAME BFSTest COMMAND bfs_exe)
