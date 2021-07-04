#pragma once

#include <array>
#include <string>
#include <vector>

#include <dubu_serialize/dubu_serialize.hpp>
#include <gmock/gmock.h>

template <typename T>
void WriteTest(dubu::serialize::WriteBuffer& buffer, const T& value) {
    buffer << value;
}

template <typename T>
void ReadTest(dubu::serialize::ReadBuffer& buffer, const T& expectedValue) {
    T value;
    buffer >> value;
    EXPECT_EQ(value, expectedValue);
}

struct Vector3 {
    float x, y, z;

    void Serialize(dubu::serialize::ReadBuffer& buffer) {
        buffer >> x;
        buffer >> y;
        buffer >> z;
    }
    void Serialize(dubu::serialize::WriteBuffer& buffer) const {
        buffer << x;
        buffer << y;
        buffer << z;
    }
};

inline bool operator==(const Vector3& lhs, const Vector3& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}

struct Mesh {
    std::vector<uint32_t> indices;
    std::vector<Vector3>  vertices;
    std::vector<Vector3>  normals;

    void Serialize(dubu::serialize::ReadBuffer& buffer) {
        buffer >> indices;
        buffer >> vertices;
        buffer >> normals;
    }
    void Serialize(dubu::serialize::WriteBuffer& buffer) const {
        buffer << indices;
        buffer << vertices;
        buffer << normals;
    }
};

inline bool operator==(const Mesh& lhs, const Mesh& rhs) {
    return (lhs.indices == rhs.indices) && (lhs.vertices == rhs.vertices) &&
           (lhs.normals == rhs.normals);
}
