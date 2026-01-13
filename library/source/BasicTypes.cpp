#include "ReStructer/Reading.hpp"
#include "ReStructer/Writing.hpp"

#include "ReStructer/private/Byteswaps.hpp"

#include <bit>

using namespace ReStructer;



#define BasicEntry(Type) \
template<> \
void ReStructer::ReadValue<Type>(Type& v, std::istream& stream) \
{ \
    stream.read(reinterpret_cast<char*>(&v), sizeof(Type)); \
} \
\
template<> \
void ReStructer::ReadBigEndian<Type>(Type& v, std::istream& stream) \
{ \
    stream.read(reinterpret_cast<char*>(&v), sizeof(Type)); \
    if constexpr (sizeof(Type) >= 1 && !Private::IsBigEndian()) { \
        v = Private::Swap(v);\
    } \
} \
template<> \
void ReStructer::ReadLittleEndian<Type>(Type& v, std::istream& stream) \
{ \
    stream.read(reinterpret_cast<char*>(&v), sizeof(Type)); \
    if constexpr (sizeof(Type) >= 1 && Private::IsBigEndian()) { \
        v = Private::Swap(v);\
    } \
} \
template<> \
void ReStructer::WriteValue<Type>(const Type& v, std::ostream& stream) \
{ \
    stream.write(reinterpret_cast<const char*>(&v), sizeof(Type)); \
} \
\
template<> \
void ReStructer::WriteBigEndian<Type>(const Type& v, std::ostream& stream) \
{ \
    if constexpr (sizeof(Type) >= 1 && !Private::IsBigEndian()) { \
        const Type v2 = Private::Swap(v);\
        stream.write(reinterpret_cast<const char*>(&v2), sizeof(Type)); \
        return;\
    } else { \
        stream.write(reinterpret_cast<const char*>(&v), sizeof(Type)); \
    }\
} \
template<> \
void ReStructer::WriteLittleEndian<Type>(const Type& v, std::ostream& stream) \
{ \
    if constexpr (sizeof(Type) >= 1 && Private::IsBigEndian()) { \
        const Type v2 = Private::Swap(v);\
        stream.write(reinterpret_cast<const char*>(&v2), sizeof(Type)); \
        return;\
    } else { \
        stream.write(reinterpret_cast<const char*>(&v), sizeof(Type)); \
    }\
}

// ReSharper disable once CppUnusedIncludeDirective
#include "ReStructer/private/BasicEntries.hpp"
