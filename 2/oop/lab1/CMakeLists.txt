cmake_minimum_required(VERSION 3.10)
project(lab0)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-g -rdynamic)

add_subdirectory(lib/googletest)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR})

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

add_library(my_lib ${SOURCES})

add_executable(my_exe main.cpp)

target_link_libraries(my_exe PRIVATE my_lib)

add_executable(my_test ${TEST_SOURCES})

target_include_directories(my_test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(my_test PRIVATE my_lib gtest gtest_main)