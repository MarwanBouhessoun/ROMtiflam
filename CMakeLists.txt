cmake_minimum_required(VERSION 3.15)
project(ROMtiflam VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ROMtiflam
    src/main.cpp
    src/core/system.cpp
    src/core/mmu.cpp
    src/cpu/arm9/arm9.cpp
    src/cpu/arm9/decode9.cpp
    src/cpu/arm7/arm7.cpp
    src/cpu/arm7/decode7.cpp
    src/hw/ipc.cpp
    src/hw/timer.cpp
)
target_include_directories(ROMtiflam PRIVATE include)
target_compile_options(ROMtiflam PRIVATE -Wall -Wextra -O3 -fno-rtti -fno-exceptions)

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(CRITERION REQUIRED criterion)

add_executable(unit_tests
    tests/test_mmu.cpp
    tests/test_arm9.cpp
    src/core/mmu.cpp
    src/cpu/arm9/arm9.cpp
)
target_include_directories(unit_tests PRIVATE include ${CRITERION_INCLUDE_DIRS})
target_link_directories(unit_tests PRIVATE ${CRITERION_LIBRARY_DIRS})
target_link_libraries(unit_tests PRIVATE ${CRITERION_LIBRARIES})
target_compile_options(unit_tests PRIVATE -Wall -Wextra)

add_test(NAME MMUTests COMMAND unit_tests)