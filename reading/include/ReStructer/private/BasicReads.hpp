// ReSharper disable once CppMissingIncludeGuard
BasicRead(uint8_t)
BasicRead( int8_t)
BasicRead(uint16_t)
BasicRead( int16_t)
BasicRead(uint32_t)
BasicRead( int32_t)
BasicRead(uint64_t)
BasicRead( int64_t)
BasicRead(char)
BasicRead(bool)
BasicRead(char8_t)
BasicRead(char16_t)
BasicRead(char32_t)

#ifndef RESTRUCTER_NOFLOAT
static_assert(sizeof(float) * CHAR_BIT == 32);
BasicRead(float)
static_assert(sizeof(double) * CHAR_BIT == 64);
BasicRead(double)
#endif