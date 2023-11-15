#include "mem/mem.h"

#include <assert.h>

void* mem_alloc_align(Allocator allocator, usize alignment, usize size) {
    return allocator.vtable.alloc(allocator.ptr, alignment, size);
}

void* mem_realloc_align(Allocator allocator, void* ptr, usize alignment, usize size) {
    return allocator.vtable.realloc(allocator.ptr, ptr, alignment, size);
}

void mem_free(Allocator allocator, void* ptr) {
    allocator.vtable.free(allocator.ptr, ptr);
}

bool mem_is_power_of_two(usize n) {
    return (n & (n - 1)) == 0;
}

usize mem_align_forward(usize n, usize align) {
    assert(mem_is_power_of_two(n));

    usize result = n + align - 1;
    result &= ~(align - 1);

    return result;
}

