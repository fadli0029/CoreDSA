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
add_test(NAME DFSTest COMMAND dfs_exe)

# Add bfs
add_executable(bfs_exe graph/bfs.cpp)
target_include_directories(bfs_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(bfs_exe Catch2::Catch2WithMain)
add_test(NAME BFSTest COMMAND bfs_exe)

# Add dijkstra
add_executable(dijkstra_exe graph/dijkstra.cpp)
target_include_directories(dijkstra_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(dijkstra_exe Catch2::Catch2WithMain)
add_test(NAME DijkstraTest COMMAND dijkstra_exe)

# Add bellman-ford
add_executable(bellman_ford_exe graph/bellman_ford.cpp)
target_include_directories(bellman_ford_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(bellman_ford_exe Catch2::Catch2WithMain)
add_test(NAME BellmanFordTest COMMAND bellman_ford_exe)

# Add quicksort
add_executable(quick_sort_exe sorting/quick_sort.cpp)
target_include_directories(quick_sort_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(quick_sort_exe Catch2::Catch2WithMain)
add_test(NAME QuickSortTest COMMAND quick_sort_exe)

# Add quickselect
add_executable(quick_select_exe sorting/quick_select.cpp)
target_include_directories(quick_select_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(quick_select_exe Catch2::Catch2WithMain)
add_test(NAME QuickSelectTest COMMAND quick_select_exe)

# Add kahn
add_executable(kahn_exe graph/kahn.cpp)
target_include_directories(kahn_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(kahn_exe Catch2::Catch2WithMain)
add_test(NAME KahnTest COMMAND kahn_exe)
