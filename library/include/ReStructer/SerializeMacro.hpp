#pragma once
#include "ReStructer/private/map.h"
#include "ReStructer/Reading.hpp"
#include "ReStructer/Writing.hpp"

#define ReStructer_ReadEntry(Func, A) Read##Func##(v.A, stream);
#define ReStructer_ReadEntryL(data) ReStructer_ReadEntry##data

#define ReStructer_WriteEntry(Func, A) Write##Func##(v.A, stream);
#define ReStructer_WriteEntryL(data) ReStructer_WriteEntry##data

#define ReStructer_SerializeProfile(StructName, ...) \
template<> \
void ReStructer::ReadValue(StructName& v, std::istream& stream) \
{ \
MAP_UD(ReStructer_ReadEntryL, StructName, __VA_ARGS__) \
} \
template<> \
void ReStructer::WriteValue(const StructName& v, std::ostream& stream) \
{ \
MAP_UD(ReStructer_WriteEntryL, StructName, __VA_ARGS__) \
}