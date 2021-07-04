#include "Common.hpp"

TEST(file_buffer, single_int) {
	const char* fileName      = "single_int.bin";
	uint32_t    expectedValue = 0xCC00FFEE;
	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);
		WriteTest(fileBuffer, expectedValue);
		EXPECT_EQ(fileBuffer.Tell<int>(), 4);
	}
	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);
		ReadTest(fileBuffer, expectedValue);
		EXPECT_EQ(fileBuffer.Tell<int>(), 4);
	}
}

TEST(file_buffer, single_string) {
	const char* fileName      = "single_string.bin";
	std::string expectedValue = "Hello World!";
	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);
		WriteTest(fileBuffer, expectedValue);
		EXPECT_EQ(fileBuffer.Tell<int>(), 16);
	}
	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);
		ReadTest(fileBuffer, expectedValue);
		EXPECT_EQ(fileBuffer.Tell<int>(), 16);
	}
}

TEST(file_buffer, single_vector_int) {
	const char*      fileName = "single_vector_int.bin";
	std::vector<int> expectedValue{9, 12, 35, 23, 58, 93, 12};

	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);
		WriteTest(fileBuffer, expectedValue);
		EXPECT_EQ(fileBuffer.Tell<int>(), 32);
	}
	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);
		ReadTest(fileBuffer, expectedValue);
		EXPECT_EQ(fileBuffer.Tell<int>(), 32);
	}
}

TEST(file_buffer, single_array_int) {
	const char*        fileName = "single_array_int.bin";
	std::array<int, 7> expectedValue{9, 12, 35, 23, 58, 93, 12};

	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);
		WriteTest(fileBuffer, expectedValue);
		EXPECT_EQ(fileBuffer.Tell<int>(), 28);
	}
	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);
		ReadTest(fileBuffer, expectedValue);
		EXPECT_EQ(fileBuffer.Tell<int>(), 28);
	}
}

TEST(file_buffer, nested_vector_string) {
	const char*                           fileName = "nested_vector_string.bin";
	std::vector<std::vector<std::string>> expectedValue{{"hello", "world"}, {"bye", "world"}};
	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);
		WriteTest(fileBuffer, expectedValue);
	}
	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);
		ReadTest(fileBuffer, expectedValue);
	}
}

TEST(file_buffer, filesystem_path) {
	const char*                        fileName      = "filesystem_path.bin";
	std::vector<std::filesystem::path> expectedValue = {
	    "dubu/portable.format",
	    "dubu\\native.format",
#ifdef _WIN32
	    L"두부/wide.portable.format",
	    L"두부\\wide.native.format",
#endif
	};

	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);
		WriteTest(fileBuffer, expectedValue);
	}
	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);
		ReadTest(fileBuffer, expectedValue);
	}
}

TEST(file_buffer, custom_mesh_struct) {
	const char* fileName = "custom_mesh_struct.bin";
	Mesh        expectedValue{.indices = {1, 2, 3}, .vertices{{3}, {2}, {1}}, .normals = {{2}, {1}, {3}}};

	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);
		WriteTest(fileBuffer, expectedValue);
	}
	{
		dubu::serialize::FileBuffer fileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);
		ReadTest(fileBuffer, expectedValue);
	}
}
