cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT wordPack)

project(${PROJECT})

file(GLOB SOURCE *.cpp)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(${PROJECT} ${SOURCE})

target_link_libraries(${PROJECT} gtest gtest_main)