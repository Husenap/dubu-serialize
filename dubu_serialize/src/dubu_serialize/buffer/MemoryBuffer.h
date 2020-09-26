#pragma once

#include <sstream>

#include "Buffer.h"

namespace dubu::serialize {

class MemoryBuffer : public ReadBuffer, public WriteBuffer {
public:
	MemoryBuffer() {}

	/**
	 * Get the position of the write pointer in the stream.
	 * @return The position of the write pointer.
	 */
	template <typename T>
	T TellP() {
		return static_cast<T>(mStream.tellp());
	}
	/**
	 * Get the position of the read pointer in the stream.
	 * @return The position of the read pointer.
	 */
	template <typename T>
	T TellG() {
		return static_cast<T>(mStream.tellg());
	}

	/**
	 * Set the position of the write pointer in the stream.
	 * @param position The desired position for the write pointer.
	 */
	template <typename T>
	void SeekP(T position) {
		mStream.seekp(static_cast<std::streampos>(position));
	}
	/**
	 * Set the position of the read pointer in the stream.
	 * @param position The desired position for the read pointer.
	 */
	template <typename T>
	void SeekG(T position) {
		mStream.seekg(static_cast<std::streampos>(position));
	}

	void Read(char* data, uint32_t size) override { mStream.read(data, static_cast<std::streamsize>(size)); }
	void Write(const char* data, uint32_t size) override { mStream.write(data, static_cast<std::streamsize>(size)); }

private:
	std::stringstream mStream;
};

}  // namespace dubu::serialize