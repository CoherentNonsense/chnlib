#include "dynarray.h"

#include <string.h>


static DynArrayHeader* get_header(const void* array) {
    return (DynArrayHeader*)((u8*)array - sizeof(DynArrayHeader));
}

static void resize(void* array, usize size, usize new_cap) {
    DynArrayHeader* header = get_header(array);
    header = realloc(header, sizeof(DynArrayHeader) + (size * new_cap));
}

static void reserve(void* array, usize size, usize elems) {
    DynArrayHeader* header = get_header(array);
    if (header->len + elems > header->cap) {
        resize(array, size, (header->cap * 1.5) + 8);
    }
}

void* dynarray_init(void) {
    DynArrayHeader* header = malloc(sizeof(DynArrayHeader*));

    header->len = 0;
    header->cap = 0;

    return (u8*)header + sizeof(DynArrayHeader);
}

void internal__dynarray_push(void* const array, const usize size, const void* const value) {
    DynArrayHeader* header = get_header(array);

    reserve(array, size, 1);

    memcpy((u8*)array + (header->len * size), value, size);

    header->len += 1;
}

void* internal__dynarray_add(void* const array, const usize size) {
    DynArrayHeader* header = get_header(array);

    reserve(array, size, 1);

    void* new_elem = (u8*)array + (header->len * size);

    header->len += 1;

    return new_elem;
}

usize dynarray_len(const void* const array) {
    DynArrayHeader* header = get_header(array);

    return header->len;
}
