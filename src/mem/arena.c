#include "mem/arena.h"

#include "mem/mem.h"
#include "logger.h"
#include <assert.h>
#include <stddef.h>

AllocatorVTable arena_vtable = {
    .alloc = arena_alloc,
    .realloc = arena_realloc,
    .free = arena_free
};


ArenaAllocator arena_init(usize block_size) {
    // TODO: pass in c_allocator
    ArenaAllocatorBlock* block = malloc(offsetof(ArenaAllocatorBlock, data) + block_size);
    block->prev = null;
    block->used = 0;

    ArenaAllocator arena = {
        .cur = block,
        .block_size = block_size,
    };

    return arena;
}

void arena_deinit(ArenaAllocator* arena) {
    while (arena->cur != null) {
        ArenaAllocatorBlock* tmp = arena->cur;
        arena->cur = tmp->prev;
        free(tmp);
    }
}

Allocator arena_allocator(ArenaAllocator* arena) {
    return (Allocator){
        .ptr = arena,
        .vtable = arena_vtable,
    };
}

void* arena_alloc(void* arena_opaque, usize alignment, usize size) {
    ArenaAllocator* arena = arena_opaque;

    usize next = mem_align_forward(arena->cur->used, alignment);

    if (next + size > arena->block_size) {
        next = 0;

        ArenaAllocatorBlock* new_block = malloc(offsetof(ArenaAllocatorBlock, data) + arena->block_size);
        new_block->used = 0;
        new_block->prev = arena->cur;
        arena->cur = new_block;
    }

    arena->cur->used = next + size;

    return (void*)next;
}

void* arena_realloc(void* arena_opaque, void* ptr, usize alignment, usize size) {
    (void)arena_opaque;
    (void)ptr;
    (void)alignment;
    (void)size;

    return null;
}

void arena_free(void* arena_opaque, void* ptr) {
    // does nothing
    (void)arena_opaque;
    (void)ptr;
}
