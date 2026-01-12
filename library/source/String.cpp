#include "ReStructer/Reading.hpp"
#include "ReStructer/Writing.hpp"

template<>
void ReStructer::ReadValue(std::string& v, std::ifstream& stream)
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

constexpr static char NullChar = '\0';

template<>
void ReStructer::WriteValue(const std::string& v, std::ofstream& stream)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        ReStructer::WriteValue(v[i], stream);
    }
    ReStructer::WriteValue(NullChar, stream);
}