# Usage
Include `"ReStructer/Reading.hpp"` for reading functions.
- ReadValue - Reads data from the stream. If this is a number-based format, it will read using the native endian format.
    - Do not use for number types if your data may be cross-platform (i.e. asset files)
- ReadBigEndian - Reads the data in big endian format. Only exists for numeric types. (and types based off of numeric types, such as arrays of numbers)
- ReadLittleEndian - Reads the data in little endian format. Only exists for numeric types. (and types based off of numeric types, such as arrays of numbers)
    - Because most modern platforms are little-endian, this is recommended if an endianness needs to be chosen.

Include `"ReStructer/Writing.hpp"` for writing functions.
- WriteValue - Writes data to the stream. If this is a number-based format, it will write using the native endian format.
    - Do not use for number types if your data may be cross-platform (i.e. asset files)
- WriteBigEndian - Writes the data in big endian format. Only exists for numeric types. (and types based off of numeric types, such as arrays of numbers)
- WriteLittleEndian - Writes the data in little endian format. Only exists for numeric types. (and types based off of numeric types, such as arrays of numbers)
    - Because most modern platforms are little-endian, this is recommended if an endianness needs to be chosen.

You can define your own custom ReadValue and WriteValue functions as needed.
They will be used automatically for container subtemplates (i.e. an array of your own custom struct.)

Include `"ReStructer/SerializeMacro.hpp"` for a macro that can auto-generate identical Writing and Reading functions for you.

To use:

- Call the macro `ReStructer_SerializeProfile` outside of any namespace.
- The first parameter must be the name of your struct (including namespaces).
- The following parameters must be grouped with parentheses `()`, each in pairs.
  - The first of each pair should be the type of read/write to use.
    - `Value` will read it normally, and if it is a numeric-based type, using the native endianness of the platform.
    - `BigEndian` or `LittleEndian` will read it with the appropriate endianness.
  - The second of each pair should be the name of the parameter to read/write.
  - Ordering of these pairs determines the order these values are serialized in.

Example:
```c++
namespace MyNamespace{
    struct ExampleStruct
    {
        uint32_t a;
        uint32_t b;
        std::string c;
    };
}
ReStructer_SerializeProfile(MyNamespace::ExampleStruct,
    (LittleEndian, a),
    (BigEndian, b),
    (Value, c)
)
```