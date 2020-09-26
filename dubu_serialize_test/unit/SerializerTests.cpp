#include <string>

#include <dubu_serialize/Serializer.h>
#include <gmock/gmock.h>

TEST(dubu_serialize, single_int) {
	const char* fileName      = "single_int.bin";
	uint32_t    expectedValue = 0xC0FFEE;

	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);

		fileBuffer << expectedValue;

		EXPECT_EQ(fileBuffer.Tell<int>(), 4);
	}

	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);

		uint32_t value;
		fileBuffer >> value;

		EXPECT_EQ(fileBuffer.Tell<int>(), 4);
		EXPECT_EQ(value, expectedValue);
	}
}

TEST(dubu_serialize, single_string) {
	const char* fileName      = "single_string.bin";
	std::string expectedValue = "Hello World!";

	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);

		fileBuffer << expectedValue;

		EXPECT_EQ(fileBuffer.Tell<int>(), 16);
	}

	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);

		std::string value;
		fileBuffer >> value;

		EXPECT_EQ(value, expectedValue);
		EXPECT_EQ(fileBuffer.Tell<int>(), 16);
	}
}

TEST(dubu_serialize, single_vector_int) {
	const char*      fileName = "single_vector_int.bin";
	std::vector<int> expectedValue{9, 12, 35, 23, 58, 93, 12};

	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);

		fileBuffer << expectedValue;

		EXPECT_EQ(fileBuffer.Tell<int>(), 32);
	}

	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);

		std::vector<int> value;
		fileBuffer >> value;

		EXPECT_THAT(value, testing::ElementsAreArray(expectedValue));
		EXPECT_EQ(fileBuffer.Tell<int>(), 32);
	}
}

TEST(dubu_serialize, nested_vector_string) {
	const char*                           fileName = "nested_vector_string.bin";
	std::vector<std::vector<std::string>> expectedValue{{"hello", "world"}, {"bye", "world"}};

	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Write);

		fileBuffer << expectedValue;
	}

	{
		auto fileBuffer = dubu::serialize::FileBuffer(fileName, dubu::serialize::FileBuffer::Mode::Read);

		std::vector<std::vector<std::string>> value;
		fileBuffer >> value;

		EXPECT_THAT(value, testing::ElementsAreArray(expectedValue));
	}
}
