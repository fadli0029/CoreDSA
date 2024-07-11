cmake_minimum_required(VERSION 3.12)
project(DS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
find_package(Catch2 3 REQUIRED)

# Add LinkedList
add_executable(LinkedList_exe LinkedList/main.cpp LinkedList/linkedlist.h)
target_include_directories(LinkedList_exe PUBLIC ${Catch2_INCLUDE_DIRS})
target_link_libraries(LinkedList_exe Catch2::Catch2)
add_test(NAME LinkedListTest COMMAND LinkedList_exe)


# Add Stack
# ...

# Add Queue
# ...
