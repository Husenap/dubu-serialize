set(target_name "dubu_serialize_test")

set(src_files
    "unit/Common.h"
    "unit/MemoryBufferTests.cpp"
    "unit/FileBufferTests.cpp")

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name}
    gmock_main
    dubu_serialize)

set_target_properties(${target_name} PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER}/test)

gtest_discover_tests(${target_name})
