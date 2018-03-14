cmake_minimum_required(VERSION 3.8)

project(propagate_const)

if(MSVC)
  add_compile_options("/EHsc")
else()
  add_compile_options("-std=gnu++14")
  set(CMAKE_CXX_FLAGS_SANITIZE "-fsanitize=address,undefined")
  set(CMAKE_EXE_LINKER_FLAGS_SANITIZE "-fsanitize=address,undefined")
endif()

if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
  add_compile_options("-Werror;-Wall")
endif()

include_directories(${CMAKE_SOURCE_DIR})
add_executable(test_propagate_const test_propagate_const.cpp)

enable_testing()
add_test(
  NAME test_propagate_const
  COMMAND test_propagate_const
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

