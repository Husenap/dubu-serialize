#pragma once

#include "Endian.hpp"
#include "dubu_serialize/buffer/Buffer.hpp"

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
		if constexpr (Endian::big) {
			FlipEndian(object);
		}
	}
	void Write(WriteBuffer& buffer, const T& object) {
		if constexpr (Endian::big) {
			T objectCopy(object);
			FlipEndian(objectCopy);
			buffer.Write(reinterpret_cast<const char*>(&objectCopy), sizeof(T));
		} else {
			buffer.Write(reinterpret_cast<const char*>(&object), sizeof(T));
		}
	}
};

template <typename T>
struct Serializer<std::basic_string<T>, false> {
	void Read(ReadBuffer& buffer, std::basic_string<T>& object) {
		uint32_t size;
		buffer >> size;
		object.resize(static_cast<std::size_t>(size));
		buffer.Read(reinterpret_cast<char*>(&object[0]), size * sizeof(T));
	}
	void Write(WriteBuffer& buffer, const std::basic_string<T>& object) {
		uint32_t size = static_cast<uint32_t>(object.size());
		buffer << size;
		buffer.Write(reinterpret_cast<const char*>(&object[0]), size * sizeof(T));
	}
};

template <>
struct Serializer<std::filesystem::path, false> {
	void Read(ReadBuffer& buffer, std::filesystem::path& object) {
		std::u8string temp;
		buffer >> temp;
		object = temp;
	}
	void Write(WriteBuffer& buffer, const std::filesystem::path& object) { buffer << object.u8string(); }
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

template <typename T, std::size_t Size>
struct Serializer<std::array<T, Size>, false> {
	void Read(ReadBuffer& buffer, std::array<T, Size>& arr) {
		for (auto& object : arr) {
			buffer >> object;
		}
	}
	void Write(WriteBuffer& buffer, const std::array<T, Size>& arr) {
		for (const auto& object : arr) {
			buffer << object;
		}
	}
};

template <typename T, std::size_t Size>
struct Serializer<T[Size], false> {
	void Read(ReadBuffer& buffer, T arr[Size]) {
		for (size_t i = 0; i < Size; ++i) {
			buffer >> arr[i];
		}
	}
	void Write(WriteBuffer& buffer, const T arr[Size]) {
		for (size_t i = 0; i < Size; ++i) {
			buffer << arr[i];
		}
	}
};

}  // namespace dubu::serialize::internal
