#ifndef CHN_MEM_ARENA_H
#define CHN_MEM_ARENA_H

#include "chntype.h"
#include "mem.h"
#include <stdalign.h>
#include <stddef.h>


typedef struct ArenaAllocator {
    struct ArenaAllocator* prev;
    usize used;
    alignas(max_align_t) u8 data[];
} ArenaAllocatorBlock;

typedef struct {
    ArenaAllocatorBlock* cur;
    usize block_size;
} ArenaAllocator;

AllocatorVTable arena_vtable;

ArenaAllocator arena_init(const usize block_size);
void arena_deinit(ArenaAllocator* arena);
Allocator arena_allocator(ArenaAllocator* arena);

void* arena_alloc(void* arena, usize alignment, usize size);
void* arena_realloc(void* arena, void* ptr, usize alignment, usize size);
void arena_free(void* arena, void* ptr);


#endif
