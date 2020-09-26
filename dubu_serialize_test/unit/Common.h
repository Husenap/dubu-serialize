#pragma once

#include <dubu_serialize/dubu_serialize.h>
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
