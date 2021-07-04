set(target_name "dubu_serialize")

set(src_buffer
    "src/dubu_serialize/buffer/Buffer.hpp"
    "src/dubu_serialize/buffer/FileBuffer.hpp"
    "src/dubu_serialize/buffer/MemoryBuffer.hpp")

set(src_serializer
    "src/dubu_serialize/serializer/Endian.hpp"
    "src/dubu_serialize/serializer/Serializer.hpp")

set(src_serialize
    "src/dubu_serialize/dubu_serialize.hpp"
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
