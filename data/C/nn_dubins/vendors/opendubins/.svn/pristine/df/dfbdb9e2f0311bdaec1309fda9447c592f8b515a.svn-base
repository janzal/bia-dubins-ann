cmake_minimum_required(VERSION 2.8)
project(planning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("include" "../core/include")

set(SOURCE_FILES
        src/shape/shape.cpp
        src/shape/ellipse.cpp
        src/shape/polygon.cpp
        src/shape/shapecircle.cpp
        src/shape/shapepoint.cpp
        src/touring/dtp.cpp
        src/touring/dubins3point.cpp
        ${PLANNING_SRC})

add_library(opendubins_planning STATIC ${SOURCE_FILES})

if (GTEST_FOUND)

    add_executable(planning_test
            test/closeststatetest.cpp
            test/dubins3pointtest.cpp
            )


    target_link_libraries(planning_test opendubins_planning)
    target_link_libraries(planning_test opendubins_core)
    target_link_libraries(planning_test ${GTEST_BOTH_LIBRARIES})
    target_link_libraries(planning_test pthread)

    add_test(planning_all_tests planning_test)

endif ()