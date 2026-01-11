#pragma once

template<typename T>
struct IsStdArrayStruct : std::false_type {};

template<typename T, std::size_t N>
struct IsStdArrayStruct<std::array<T, N>> : std::true_type {};

template<typename T>
concept IsStdArray = IsStdArrayStruct<T>::value;

template<typename T>
struct IsStdVectorStruct : std::false_type {};

template<typename T, typename A>
struct IsStdVectorStruct<std::vector<T, A>> : std::true_type {};

template<typename T>
concept IsStdVector = IsStdVectorStruct<T>::value;
