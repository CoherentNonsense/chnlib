#ifndef CHN_DYNARRAY_H
#define CHN_DYNARRAY_H

#include "chntype.h"

#define DynArray(T) T*

void* dynarray_init(void);
void dynarray_deinit(void* array);

usize dynarray_len(const void* const array);

void  internal__dynarray_push(void** const array, const usize size, const void* const value);
#define dynarray_push(array, value) do { \
    __typeof__(array) tmp = value;       \
    internal__dynarray_push(             \
        (void** const)&array,            \
        sizeof(*array),                  \
        tmp                              \
    );                                   \
} while(0)

void* internal__dynarray_add(void** const array, const usize size);
#define dynarray_add(array) (__typeof__(array))internal__dynarray_add((void** const)&array, sizeof(*array))

#endif
