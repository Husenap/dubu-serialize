#include "Common.h"

TEST(memory_buffer, single_int) {
	uint32_t expectedValue  = 0xCC00FFEE;
	uint32_t expectedValue2 = 0xDEADBEEF;
	{
		dubu::serialize::MemoryBuffer memoryBuffer;

		EXPECT_EQ(memoryBuffer.TellG<int>(), 0);
		EXPECT_EQ(memoryBuffer.TellP<int>(), 0);

		WriteTest(memoryBuffer, expectedValue);

		EXPECT_EQ(memoryBuffer.TellG<int>(), 0);
		EXPECT_EQ(memoryBuffer.TellP<int>(), 4);

		ReadTest(memoryBuffer, expectedValue);

		EXPECT_EQ(memoryBuffer.TellG<int>(), 4);
		EXPECT_EQ(memoryBuffer.TellP<int>(), 4);

		WriteTest(memoryBuffer, expectedValue2);

		EXPECT_EQ(memoryBuffer.TellG<int>(), 4);
		EXPECT_EQ(memoryBuffer.TellP<int>(), 8);

		ReadTest(memoryBuffer, expectedValue2);

		EXPECT_EQ(memoryBuffer.TellG<int>(), 8);
		EXPECT_EQ(memoryBuffer.TellP<int>(), 8);

		memoryBuffer.SeekG(0);
		memoryBuffer.SeekP(0);

		EXPECT_EQ(memoryBuffer.TellG<int>(), 0);
		EXPECT_EQ(memoryBuffer.TellP<int>(), 0);

		WriteTest(memoryBuffer, expectedValue2);
		ReadTest(memoryBuffer, expectedValue2);

		EXPECT_EQ(memoryBuffer.TellG<int>(), 4);
		EXPECT_EQ(memoryBuffer.TellP<int>(), 4);
	}
}

TEST(memory_buffer, single_string) {
	std::string expectedValue = "Hello World!";
	{
		dubu::serialize::MemoryBuffer memoryBuffer;
		WriteTest(memoryBuffer, expectedValue);
		ReadTest(memoryBuffer, expectedValue);
	}
}

TEST(memory_buffer, single_vector_int) {
	std::vector<int> expectedValue{9, 12, 35, 23, 58, 93, 12};
	{
		dubu::serialize::MemoryBuffer memoryBuffer;
		WriteTest(memoryBuffer, expectedValue);
		ReadTest(memoryBuffer, expectedValue);
	}
}

TEST(memory_buffer, single_array_int) {
	std::array<int, 7> expectedValue{9, 12, 35, 23, 58, 93, 12};

	{
		dubu::serialize::MemoryBuffer memoryBuffer;
		WriteTest(memoryBuffer, expectedValue);

		EXPECT_EQ(memoryBuffer.TellG<int>(), 0);
		EXPECT_EQ(memoryBuffer.TellP<int>(), 28);

		ReadTest(memoryBuffer, expectedValue);

		EXPECT_EQ(memoryBuffer.TellG<int>(), 28);
		EXPECT_EQ(memoryBuffer.TellP<int>(), 28);
	}
}

TEST(memory_buffer, nested_vector_string) {
	std::vector<std::vector<std::string>> expectedValue{{"hello", "world"}, {"bye", "world"}};
	{
		dubu::serialize::MemoryBuffer memoryBuffer;
		WriteTest(memoryBuffer, expectedValue);
		ReadTest(memoryBuffer, expectedValue);
	}
}

TEST(memory_buffer, filesystem_path) {
	std::vector<std::filesystem::path> expectedValue = {
	    "dubu/portable.format",
	    "dubu\\native.format",
#ifdef _WIN32
	    L"두부/wide.portable.format",
	    L"두부\\wide.native.format",
#endif
	};
	{
		dubu::serialize::MemoryBuffer memoryBuffer;
		WriteTest(memoryBuffer, expectedValue);
		ReadTest(memoryBuffer, expectedValue);
	}
}

TEST(memory_buffer, custom_mesh_struct) {
	Mesh expectedValue{.indices = {1, 2, 3}, .vertices{3, 2, 1}, .normals = {2, 1, 3}};
	{
		dubu::serialize::MemoryBuffer memoryBuffer;
		WriteTest(memoryBuffer, expectedValue);
		ReadTest(memoryBuffer, expectedValue);
	}
}
