#include "mem/arena.h"

#include "logger.h"
#include <assert.h>


int main(void) {
    chn_info("testing arena allocator");
    {
        ArenaAllocator arena = arena_init(64);
        Allocator allocator = arena_allocator(&arena);

        mem_alloc_ty(allocator, u32);
        assert(arena.cur->used == 4 and "allocate 4 bytes");

        mem_alloc_ty(allocator, u64);
        assert(arena.cur->used == 16 and "add padding");

        mem_alloc(allocator, 64 - 16);
        assert(arena.cur->used == 64 and "arena is full");

        mem_alloc_ty(allocator, u32);
        assert(arena.cur->used == 4 and "create new block");

        arena_deinit(&arena);
    }
    chn_info("testing arena allocator (SUCCESS)");
}
