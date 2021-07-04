#pragma once

#include <cstdint>

namespace dubu::serialize {

class ReadBuffer {
public:
    virtual ~ReadBuffer()                            = default;
    virtual void Read(char* data, uint32_t numBytes) = 0;
};

class WriteBuffer {
public:
    virtual ~WriteBuffer()                                  = default;
    virtual void Write(const char* data, uint32_t numBytes) = 0;
};

}  // namespace dubu::serialize