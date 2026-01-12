#include <filesystem>
#include <iostream>

#include "ReStructer/Reading.hpp"
#include "ReStructer/Writing.hpp"

struct TestStruct
{
    uint32_t a;
};

template<>
void ReStructer::ReadValue(TestStruct& v, std::ifstream& stream)
{
    ReadBigEndian(v.a, stream);
}

template<>
void ReStructer::WriteValue(const TestStruct& v, std::ofstream& stream)
{
    WriteBigEndian(v.a, stream);
}

int main()
{
    uint16_t v = 0;
    std::ifstream stream("test.bin", std::ios::binary);
    if (!stream.is_open())
    {
        std::cout << std::filesystem::current_path() << std::endl;
        return -1;
    }
    ReStructer::ReadValue(v, stream);
    std::cout << v << std::endl;

    std::array<uint16_t, 4> arr;
    ReStructer::ReadValue(arr, stream);
    for (const uint16_t val : arr)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::string msg;
    ReStructer::ReadValue(msg, stream);
    std::cout << msg << std::endl;

    std::vector<uint8_t> vecNumbers;
    ReStructer::ReadValue(vecNumbers, stream);
    for (const uint8_t val : vecNumbers)
    {
        std::cout << static_cast<int>(val) << " ";
    }
    std::cout << std::endl;

    TestStruct structTest{};
    ReStructer::ReadValue(structTest, stream);
    std::cout << structTest.a << std::endl;

    std::array<TestStruct, 2> structArray{};
    ReStructer::ReadValue(structArray, stream);
    for (const auto val : structArray)
    {
        std::cout << val.a << " ";
    }
    std::cout << std::endl;

    std::vector<TestStruct> structVec{};
    ReStructer::ReadValue(structVec, stream);
    for (const auto val : structVec)
    {
        std::cout << val.a << " ";
    }
    std::cout << std::endl;

    std::vector<uint32_t> uintVec{};
    stream.seekg((structVec.size() * -sizeof(TestStruct)) - sizeof(uint32_t), std::ios_base::cur);
    ReStructer::ReadBigEndian(uintVec, stream);
    for (const auto val : uintVec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::ofstream outstream("out.bin", std::ios::binary);
    ReStructer::WriteValue(v, outstream);
    ReStructer::WriteValue(arr, outstream);
    ReStructer::WriteValue(msg, outstream);
    ReStructer::WriteValue(vecNumbers, outstream);
    ReStructer::WriteValue(structTest, outstream);
    ReStructer::WriteValue(structArray, outstream);
    ReStructer::WriteValue(structVec, outstream);
    //ReStructer::WriteBigEndian(uintVec, outstream);
}