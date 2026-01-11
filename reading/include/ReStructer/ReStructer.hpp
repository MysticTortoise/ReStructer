#pragma once
#include <fstream>
#include <cstdint>
#include <array>
#include <vector>

namespace ReStructer
{
#include "ReStructer/private/Concepts.hpp"
    
    template<typename T> void ReadValue(T& v, std::ifstream& stream) = delete;
    template<typename T> void ReadBigEndian(T& v, std::ifstream& stream) = delete;
    template<typename T> void ReadLittleEndian(T& v, std::ifstream& stream) = delete;

#define BasicRead(Type) \
    template<> void ReadValue<Type>(Type&, std::ifstream&); \
    template<> void ReadBigEndian<Type>(Type&, std::ifstream&); \
    template<> void ReadLittleEndian<Type>(Type&, std::ifstream&);
    // ReSharper disable once CppUnusedIncludeDirective
#include "ReStructer/private/BasicReads.hpp"
#undef BasicRead

    template<>
    inline void ReadValue(std::string& v, std::ifstream& stream)
    {
        char lastVal;
        while (true)
        {
            stream.read(&lastVal, sizeof(char));
            if (lastVal == '\0')
            {
                break;
            }
            v += lastVal;
        }
    }
}
