#pragma once

#include <filesystem>
#include <fstream>

namespace dubu::serialize {

class WriteBuffer {
public:
	virtual ~WriteBuffer()                                   = default;
	virtual void Write(const char* buffer, std::size_t size) = 0;
};

class ReadBuffer {
public:
	virtual ~ReadBuffer()                             = default;
	virtual void Read(char* buffer, std::size_t size) = 0;
};

class FileBuffer : public WriteBuffer, public ReadBuffer {
public:
	enum class Mode { Read, Write };

public:
	FileBuffer(std::filesystem::path filePath, Mode mode)
	    : mMode(mode) {
		if (mMode == Mode::Read) {
			mStream.open(filePath, std::ios::in | std::ios::binary);
		} else {
			mStream.open(filePath, std::ios::out | std::ios::binary);
		}
	}
	~FileBuffer() { mStream.close(); }

	template <typename T>
	T Tell() {
		if (mMode == Mode::Read) {
			return static_cast<T>(mStream.tellg());
		} else {
			return static_cast<T>(mStream.tellp());
		}
	}

	template <typename T>
	void Seek(T position) {
		if (mMode == Mode::Read) {
			mStream.seekg(static_cast<std::streampos>(position));
		} else {
			mStream.seekp(static_cast<std::streampos>(position));
		}
	}

	void Write(const char* buffer, std::size_t size) override { mStream.write(buffer, size); }
	void Read(char* buffer, std::size_t size) override { mStream.read(buffer, size); }

private:
	std::fstream mStream;
	Mode         mMode = Mode::Read;
};

}  // namespace dubu::serialize