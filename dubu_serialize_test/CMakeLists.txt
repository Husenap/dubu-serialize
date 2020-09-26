set(target_name "dubu_serialize_test")

set(src_files
    "unit/SerializerTests.cpp")

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name}
    gtest
    gmock
    gmock_main
    dubu_serialize)

set_target_properties(${target_name} PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER}/test)

gtest_discover_tests(${target_name})
