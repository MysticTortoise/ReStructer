# Type Formats
ReStructer comes with built-in support for a number of types.

## Primitive Types:
ReStructer supports the following numeric types in both big-endian and little-endian formats:
- uint8_t
- int8_t
- uint16_t
- int16_t
- uint32_t
- int32_t
- uint64_t
- int64_t
- char
- bool
- char8_t
- char16_t
- char32_t
  
The following types are also supported only on platforms with 32 bit int and 64 bit float:
- float
- double

## Container Types:
ReStructer supports the following container types with the appropriate syntax:
- std::string - A NULL (0x00) terminated string. Characters are read until a 0x00 byte is found.
- std::array - Fixed size arrays. ReStructer will read using whatever templates are specialized for the containing type
until the array's fixed size is filled.
- std::vector - Dynamic size arrays. The first value should be a uint32_t in Little Endian format, 
representing the size of the vector. 
Then, the rest of the data is read like an std::array, filling out the vector until the size is met.

## User-Defined Types:
The user can define custom template overrides of ReadValue(), ReadBigEndian(), and ReadLittleEndian().
These will be used whenever those functions are called, including in container types.