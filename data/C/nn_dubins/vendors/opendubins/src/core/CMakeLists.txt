include_directories("include")

set(SOURCE_FILES ${DUBINS_SRC}
        src/arc.cpp
        src/circle.cpp
        src/dubins.cpp
        src/dubinsmaneuver.cpp
        src/dip.cpp
        src/gdip.cpp
        src/line.cpp
        src/path.cpp
        src/state.cpp
        )

add_library(opendubins_core STATIC ${SOURCE_FILES})

if (GTEST_FOUND)

    add_executable(dubinstest
            test/dubinstest.cpp
            test/diptest.cpp
            test/gdiptest.cpp
            )

    target_link_libraries(dubinstest opendubins_core)
    target_link_libraries(dubinstest ${GTEST_BOTH_LIBRARIES})
    target_link_libraries(dubinstest pthread)

    add_test(core_tests dubinstest)

endif ()