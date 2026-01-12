// ReSharper disable once CppMissingIncludeGuard
BasicEntry(uint8_t)
BasicEntry( int8_t)
BasicEntry(uint16_t)
BasicEntry( int16_t)
BasicEntry(uint32_t)
BasicEntry( int32_t)
BasicEntry(uint64_t)
BasicEntry( int64_t)
BasicEntry(char)
BasicEntry(bool)
BasicEntry(char8_t)
BasicEntry(char16_t)
BasicEntry(char32_t)

#ifndef RESTRUCTER_NOFLOAT
static_assert(sizeof(float) * CHAR_BIT == 32);
BasicEntry(float)
static_assert(sizeof(double) * CHAR_BIT == 64);
BasicEntry(double)
#endif