#pragma once

#include <string>
#include <vector>

#include "Buffer.h"
#include "Endian.h"

namespace dubu::serialize::internal {

template <typename T, bool IsArithmetic>
struct Serializer {
	void Read(ReadBuffer& buffer, T& object) { object.Serialize(buffer); }
	void Write(WriteBuffer& buffer, const T& object) { object.Serialize(buffer); }
};

}  // namespace dubu::serialize::internal

namespace dubu::serialize {

template <typename T>
ReadBuffer& operator>>(ReadBuffer& buffer, T& object) {
	internal::Serializer<T, std::is_arithmetic_v<std::decay_t<T>>>().Read(buffer, object);
	return buffer;
}

template <typename T>
WriteBuffer& operator<<(WriteBuffer& buffer, const T& object) {
	internal::Serializer<T, std::is_arithmetic_v<std::decay_t<T>>>().Write(buffer, object);
	return buffer;
}

}  // namespace dubu::serialize

namespace dubu::serialize::internal {

template <typename T>
struct Serializer<T, true> {
	void Read(ReadBuffer& buffer, T& object) {
		buffer.Read(reinterpret_cast<char*>(&object), sizeof(T));
		if (Endian::big) {
			FlipEndian(object);
		}
	}
	void Write(WriteBuffer& buffer, const T& object) {
		if (Endian::big) {
			T objectCopy(object);
			FlipEndian(objectCopy);
			buffer.Write(reinterpret_cast<const char*>(&objectCopy), sizeof(T));
		} else {
			buffer.Write(reinterpret_cast<const char*>(&object), sizeof(T));
		}
	}
};

template <>
struct Serializer<std::string, false> {
	void Read(ReadBuffer& buffer, std::string& object) {
		uint32_t size;
		buffer >> size;
		object.resize(static_cast<std::size_t>(size));
		buffer.Read(&object[0], static_cast<std::size_t>(size));
	}
	void Write(WriteBuffer& buffer, const std::string& object) {
		uint32_t size = static_cast<uint32_t>(object.size());
		buffer << size;
		buffer.Write(&object[0], object.size());
	}
};

template <typename T>
struct Serializer<std::vector<T>, false> {
	void Read(ReadBuffer& buffer, std::vector<T>& object) {
		uint32_t size;
		buffer >> size;
		object.resize(static_cast<std::size_t>(size));
		for (std::size_t i = 0; i < object.size(); ++i) {
			buffer >> object[i];
		}
	}
	void Write(WriteBuffer& buffer, const std::vector<T>& object) {
		buffer << static_cast<uint32_t>(object.size());
		for (std::size_t i = 0; i < object.size(); ++i) {
			buffer << object[i];
		}
	}
};

}  // namespace dubu::serialize::internal
