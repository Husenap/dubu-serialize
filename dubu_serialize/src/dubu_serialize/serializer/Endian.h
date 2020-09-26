#pragma once

namespace dubu::serialize::internal {

class Endian {
private:
	Endian()                        = delete;
	static constexpr uint32_t data  = 0x01020304;
	static constexpr uint8_t  magic = static_cast<uint8_t>(data);

public:
	static constexpr bool little = magic == 0x04;
	static constexpr bool big    = magic == 0x01;
};

template <typename T>
inline void FlipEndian(T& u) {
	union {
		T             u;
		unsigned char u8[sizeof(T)];
	} source, dest;

	source.u = u;

	for (std::size_t k = 0; k < sizeof(T); ++k) {
		dest.u8[k] = source.u8[sizeof(T) - k - 1];
	}

	u = dest.u;
}

}  // namespace dubu::serialize::internal
