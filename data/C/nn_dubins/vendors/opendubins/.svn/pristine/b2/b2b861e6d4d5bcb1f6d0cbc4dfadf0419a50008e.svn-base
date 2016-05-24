cmake_minimum_required(VERSION 2.8)
project(opendubins)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

enable_testing()
find_package(GTest)

if(GTEST_FOUND)
    MESSAGE("GTEST  OK")
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    MESSAGE("GTEST  not found")
endif()

add_subdirectory(core)
add_subdirectory(planning)

add_subdirectory(examples)