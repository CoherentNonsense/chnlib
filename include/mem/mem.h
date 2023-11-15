#ifndef CHN_MEM_H
#define CHN_MEM_H

#include "chntype.h"


typedef struct {
    void* (*alloc)(void* allocator, usize alignment, usize size);
    void* (*realloc)(void* allocator, void* ptr, usize alignment, usize size);
    void  (*free)(void* allocator, void* ptr);
} AllocatorVTable;

typedef struct {
    void* ptr;
    AllocatorVTable vtable;
} Allocator;

void* mem_alloc_align(Allocator allocator, usize alignment, usize size);
#define mem_alloc(alloc, size) mem_alloc_align(alloc, alignof(max_align_t), size)
#define mem_alloc_ty(alloc, T) mem_alloc_align(alloc, alignof(T), sizeof(T))

void* mem_realloc_align(Allocator allocator, void* ptr, usize alignment, usize size);
#define mem_realloc(alloc, ptr, alig, size) mem_realloc_align(alloc, alignof(max_align_t), alig, size)

void mem_free(Allocator allocator, void* ptr);

bool mem_is_power_of_two(usize n);
usize mem_align_forward(usize n, usize align);

#endif
