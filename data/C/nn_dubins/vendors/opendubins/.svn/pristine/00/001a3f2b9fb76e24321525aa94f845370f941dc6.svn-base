include_directories("../core/include")
include_directories("../planning/include")

add_executable(hellodubins src/hellodubins.cpp ${SOURCE_FILES} )
target_link_libraries(hellodubins opendubins_planning)
target_link_libraries(hellodubins opendubins_core)

add_executable(example3point src/example3point.cpp ${SOURCE_FILES} )
target_link_libraries(example3point opendubins_planning)
target_link_libraries(example3point opendubins_core)