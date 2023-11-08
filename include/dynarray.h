#ifndef CHN_DYNARRAY_H
#define CHN_DYNARRAY_H

#include "chntype.h"

#define DynArray(T) T*

typedef struct {
    usize len;
    usize cap;
} DynArrayHeader;

void  internal__dynarray_push(void* const array, const usize size, const void* const value);
void* internal__dynarray_add(void* const array, const usize size);
usize dynarray_len(const void* const array);

void* dynarray_init(void);
#define dynarray_deinit(array) free((u8*)array - sizeof(DynArrayHeader))

#define dynarray_push(array, value) internal__dynarray_push((void* const)array, sizeof(*array), value);
#define dynarray_add(array) (__typeof__(array))internal__dynarray_add((void* const)array, sizeof(*array))


#endif
