#include "dynarray.h"

#include <string.h>
#include "logger.h"

typedef struct {
    usize len;
    usize cap;
} DynArrayHeader;

static DynArrayHeader* get_header(const void* array) {
    return (DynArrayHeader*)((u8*)array - sizeof(DynArrayHeader));
}

static void resize(void** array, usize size, usize new_cap) {
    DynArrayHeader* header = get_header(*array);
    DynArrayHeader* new_header = realloc(header, sizeof(DynArrayHeader) + (size * new_cap));

    new_header->cap = new_cap;

    *array = (u8*)new_header + sizeof(DynArrayHeader);
}

static void reserve(void** array, usize size, usize elems) {
    DynArrayHeader* header = get_header(*array);
    if (header->len + elems > header->cap) {
        resize(array, size, (header->cap * 1.5) + 16);
    }
}

void* dynarray_init(void) {
    DynArrayHeader* header = malloc(sizeof(DynArrayHeader));

    header->len = 0;
    header->cap = 0;

    return (u8*)header + sizeof(DynArrayHeader);
}

void dynarray_deinit(void* array) {
    free((u8*)array - sizeof(DynArrayHeader));
}

void internal__dynarray_push(void** const array, const usize size, const void* const value) {
    DynArrayHeader* header = get_header(*array);

    reserve(array, size, 1);

    memcpy((u8*)*array + (header->len * size), value, size);

    header->len += 1;
}

void* internal__dynarray_add(void** const array, const usize size) {
    DynArrayHeader* header = get_header(*array);

    reserve(array, size, 1);

    void* new_elem = (u8*)*array + (header->len * size);

    header->len += 1;

    return new_elem;
}

usize dynarray_len(const void* const array) {
    DynArrayHeader* header = get_header(array);

    return header->len;
}
