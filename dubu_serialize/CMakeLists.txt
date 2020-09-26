set(target_name "dubu_serialize")

set(src_serialize
    "src/dubu_serialize/Endian.h"
    "src/dubu_serialize/Buffer.h"
    "src/dubu_serialize/Serializer.h")

set(src_files
    ${src_serialize}
    "src/dummy.cpp")

# Project
add_library(${target_name} STATIC ${src_files})

target_link_libraries(${target_name}
    compiler_features
    compiler_warnings)

source_group("src" FILES "src/main.cpp")

target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(${target_name} PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER})
