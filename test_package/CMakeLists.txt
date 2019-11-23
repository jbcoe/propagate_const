project(test_package LANGUAGES CXX)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(propagate_const REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(test_propagate_const ../test_propagate_const.cpp)
target_link_libraries(test_propagate_const PRIVATE propagate_const::propagate_const Catch2::Catch2)

enable_testing()
include(Catch)
catch_discover_tests(test_propagate_const)
