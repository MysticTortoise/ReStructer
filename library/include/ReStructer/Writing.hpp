#pragma once
#include <fstream>
#include <cstdint>
#include <array>
#include <vector>
#include <iostream>

namespace ReStructer
{
#include "ReStructer/private/Concepts.hpp"

    // Basic Template Inits
    template<typename T> void WriteValue(const T& v, std::ostream& stream) = delete;
    template<typename T> void WriteBigEndian(const T& v, std::ostream& stream) = delete;
    template<typename T> void WriteLittleEndian(const T& v, std::ostream& stream) = delete;

    // Basic Reads
#define BasicEntry(Type) \
    template<> void WriteValue<Type>(const Type&, std::ostream&); \
    template<> void WriteBigEndian<Type>(const Type&, std::ostream&); \
    template<> void WriteLittleEndian<Type>(const Type&, std::ostream&);
    // ReSharper disable once CppUnusedIncludeDirective
#include "ReStructer/private/BasicEntries.hpp"
#undef BasicEntry

    template<> void WriteValue(const std::string& v, std::ostream& stream);

    // ----------------------------------------------------------------------------------------------------------------
    // START OF SUBTEMPLATE STUFF
    // ----------------------------------------------------------------------------------------------------------------

    // Arrays
#define ArrayFunc(Func) \
    template<IsStdArray T> void Func(const T& v, std::ostream& stream) \
    { \
        for (size_t i = 0; i < v.size(); ++i) \
        { \
            Func(v[i], stream); \
        } \
    }
    ArrayFunc(WriteValue)
    ArrayFunc(WriteBigEndian)
    ArrayFunc(WriteLittleEndian)
#undef ArrayFunc

    // Vectors
#define VectorFunc(Func) \
    template<IsStdVector T> void Func(const T& v, std::ostream& stream) \
    { \
        WriteLittleEndian(static_cast<uint32_t>(v.size()), stream); \
        for (size_t i = 0; i < v.size(); i++) \
        { \
            Func(v[i], stream); \
        } \
    }

    VectorFunc(WriteValue)
    VectorFunc(WriteBigEndian)
    VectorFunc(WriteLittleEndian)
#undef VectorFunc
    
}
