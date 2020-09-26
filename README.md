![Windows](https://github.com/Husenap/cmake-project-template/workflows/Windows/badge.svg)
![Ubuntu](https://github.com/Husenap/cmake-project-template/workflows/Ubuntu/badge.svg)

```
   _     _                       _     _ _         
 _| |_ _| |_ _ _ ___ ___ ___ ___|_|___| |_|___ ___ 
| . | | | . | | |___|_ -| -_|  _| | .'| | |- _| -_|
|___|___|___|___|   |___|___|_| |_|__,|_|_|___|___|
```

C++ Serialization Library

## Features

* Serialization of standard types such as:	
	* `std::vector`
	* `std::array`
	* `std::basic_string`
	* `std::filesystem::path`
	* All arithmetic types
* Serialize function on custom types, see examples below 

## Example Usage

##### **`Buffer Types and Standard Serialization`**
```cpp
#include <dubu_serialize/dubu_serialize.h>

int main() {
	{  // Writes to a file `data.bin` that will contain the serialized binary data
		dubu::serialize::FileBuffer fileBuffer("data.bin", dubu::serialize::FileBuffer::Mode::Write);

		std::vector<uint32_t> values{3, 2, 1};
		fileBuffer << values;  // values contains {3, 2, 1}
	}
	{  // Reads from the `data.bin` file
		dubu::serialize::FileBuffer fileBuffer("data.bin", dubu::serialize::FileBuffer::Mode::Read);

		std::vector<uint32_t> values{3, 2, 1};
		fileBuffer >> values;  // values contains {3, 2, 1}
	}
	{  // Writes/Reads to/from a Memory Buffer
		dubu::serialize::MemoryBuffer memoryBuffer;

		std::vector<uint32_t> inValues{3, 2, 1};
		memoryBuffer << inValues;

		std::vector<uint32_t> outValues;
		memoryBuffer >> outValues;  // outValues contains {3, 2, 1}
	}
}
```

##### **`Custom Type Serialization`**
```cpp
#include <dubu_serialize/dubu_serialize.h>

struct Vector3 {
	float x, y, z;

	void Serialize(dubu::serialize::ReadBuffer& buffer) {
		buffer >> x;
		buffer >> y;
		buffer >> z;
	}
	void Serialize(dubu::serialize::WriteBuffer& buffer) const {
		buffer << x;
		buffer << y;
		buffer << z;
	}
};
struct Mesh {
	std::vector<uint32_t> indices;
	std::vector<Vector3>  vertices;

	void Serialize(dubu::serialize::ReadBuffer& buffer) {
		buffer >> indices;
		buffer >> vertices;
	}
	void Serialize(dubu::serialize::WriteBuffer& buffer) const {
		buffer << indices;
		buffer << vertices;
	}
};

int main() {
	{  // Save the mesh into a binary `model.bin` file
		dubu::serialize::FileBuffer fileBuffer("model.bin", dubu::serialize::FileBuffer::Mode::Write);

		Mesh mesh;  // A mesh containing data
		fileBuffer << mesh;
	}
	{  // Read the mesh from a binary `model.bin` file
		dubu::serialize::FileBuffer fileBuffer("model.bin", dubu::serialize::FileBuffer::Mode::Read);

		Mesh mesh;
		fileBuffer >> mesh;
	}
}
```