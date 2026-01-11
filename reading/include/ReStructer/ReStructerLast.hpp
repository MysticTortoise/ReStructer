#pragma once
#include <fstream>

namespace ReStructer
{
#include "ReStructer/private/Concepts.hpp"
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
