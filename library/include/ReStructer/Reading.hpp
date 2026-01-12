#pragma once
#include <fstream>
#include <cstdint>
#include <array>
#include <vector>

namespace ReStructer
{
#include "ReStructer/private/Concepts.hpp"

    // Basic Tempalte Inits
    template<typename T> void ReadValue(T& v, std::ifstream& stream) = delete;
    template<typename T> void ReadBigEndian(T& v, std::ifstream& stream) = delete;
    template<typename T> void ReadLittleEndian(T& v, std::ifstream& stream) = delete;

    // Basic Reads
#define BasicEntry(Type) \
    template<> void ReadValue<Type>(Type&, std::ifstream&); \
    template<> void ReadBigEndian<Type>(Type&, std::ifstream&); \
    template<> void ReadLittleEndian<Type>(Type&, std::ifstream&);
    // ReSharper disable once CppUnusedIncludeDirective
#include "ReStructer/private/BasicEntries.hpp"
#undef BasicEntry

    template<> void ReadValue(std::string& v, std::ifstream& stream);

    // ----------------------------------------------------------------------------------------------------------------
    // START OF SUBTEMPLATE STUFF
    // ----------------------------------------------------------------------------------------------------------------

    // Arrays
#define ArrayFunc(Func) \
    template<IsStdArray T> void Func(T& v, std::ifstream& stream) \
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
    template<IsStdVector T> void Func(T& v, std::ifstream& stream) \
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
