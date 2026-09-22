set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.13)
project(ROMtiflam CXX)

add_library(romtiflam_core STATIC)
target_include_directories(romtiflam_core PRIVATE include)
target_compile_options(romtiflam_core PRIVATE -Wall -Wextra -O3 -fno-rtti)

add_subdirectory(src)

add_executable(ROMtiflam src/main.cpp)
target_link_libraries(ROMtiflam PRIVATE romtiflam_core)

enable_testing()
add_subdirectory(tests)