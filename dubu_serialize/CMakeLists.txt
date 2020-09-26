set(target_name "dubu_serialize")

set(src_buffer
    "src/dubu_serialize/buffer/Buffer.h"
    "src/dubu_serialize/buffer/FileBuffer.h"
    "src/dubu_serialize/buffer/MemoryBuffer.h")

set(src_serializer
    "src/dubu_serialize/serializer/Endian.h"
    "src/dubu_serialize/serializer/Serializer.h")

set(src_serialize
    "src/dubu_serialize/dubu_serialize.h"
    "src/dummy.cpp")

set(src_files
    ${src_buffer}
    ${src_serializer}
    ${src_serialize})

# Project
add_library(${target_name} STATIC ${src_files})

target_link_libraries(${target_name}
    compiler_features
    compiler_warnings)

source_group("src" FILES ${src_serialize})
source_group("src/buffer" FILES ${src_buffer})
source_group("src/serializer" FILES ${src_serializer})

target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(${target_name} PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER})
