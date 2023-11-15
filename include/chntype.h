#ifndef CHN_TYPES_H
#define CHN_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <iso646.h>

typedef uint8_t u8;
typedef int8_t  i8;

typedef uint16_t u16;
typedef int16_t  i16;

typedef uint32_t u32;
typedef int32_t  i32;

typedef uint64_t u64;
typedef int64_t  i64;

typedef float f32;
typedef double f64;

typedef size_t usize;

#undef NULL // >:)
#define null ((void*)0)

#endif
