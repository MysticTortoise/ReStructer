#pragma once
#include <fstream>
#include <cstdint>
#include <array>
#include <vector>

namespace ReStructer
{
#include "ReStructer/private/Concepts.hpp"

    // Basic Tempalte Inits
    template<typename T> void ReadValue(T& v, std::istream& stream) = delete;
    template<typename T> void ReadBigEndian(T& v, std::istream& stream) = delete;
    template<typename T> void ReadLittleEndian(T& v, std::istream& stream) = delete;

    // Basic Reads
#define BasicEntry(Type) \
    template<> void ReadValue<Type>(Type&, std::istream&); \
    template<> void ReadBigEndian<Type>(Type&, std::istream&); \
    template<> void ReadLittleEndian<Type>(Type&, std::istream&);
    // ReSharper disable once CppUnusedIncludeDirective
#include "ReStructer/private/BasicEntries.hpp"
#undef BasicEntry

    template<> void ReadValue(std::string& v, std::istream& stream);

    // ----------------------------------------------------------------------------------------------------------------
    // START OF SUBTEMPLATE STUFF
    // ----------------------------------------------------------------------------------------------------------------

    // Arrays
#define ArrayFunc(Func) \
    template<IsStdArray T> void Func(T& v, std::istream& stream) \
    { \
        for (size_t i = 0; i < v.size(); ++i) \
        { \
            Func(v[i], stream); \
        } \
    }
    ArrayFunc(ReadValue)
    ArrayFunc(ReadBigEndian)
    ArrayFunc(ReadLittleEndian)
#undef ArrayFunc

    // Vectors
#define VectorFunc(Func) \
    template<IsStdVector T> void Func(T& v, std::istream& stream) \
    { \
        typename T::value_type entry; \
        uint32_t size; \
        ReadLittleEndian(size, stream); \
        for (uint32_t i = 0; i < size; i++) \
        { \
            Func(entry, stream); \
            v.push_back(entry); \
        } \
    }

    VectorFunc(ReadValue)
    VectorFunc(ReadBigEndian)
    VectorFunc(ReadLittleEndian)
#undef VectorFunc
    
}
