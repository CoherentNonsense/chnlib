#ifndef CHN_TYPES_H
#define CHN_TYPES_H

#include <stdint.h>
#include <stdlib.h>

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

typedef _Bool bool;
#define true ((bool)1)
#define false ((bool)0)

typedef size_t usize;

#define null ((void*)0)

// the best part of iso646
#define and &&
#define or ||

#endif