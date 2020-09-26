#pragma once

#include <filesystem>
#include <fstream>

#include "Buffer.h"

namespace dubu::serialize {

class FileBuffer : public ReadBuffer, public WriteBuffer {
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

	void Read(char* data, uint32_t size) override { mStream.read(data, static_cast<std::streamsize>(size)); }
	void Write(const char* data, uint32_t size) override { mStream.write(data, static_cast<std::streamsize>(size)); }

private:
	std::fstream mStream;
	Mode         mMode = Mode::Read;
};

}  // namespace dubu::serialize