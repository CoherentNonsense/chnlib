#include "map.h"

#include <stdlib.h>
#include <string.h>
#include "logger.h"

typedef struct {
    usize cap;
    usize len;
} MapHeader;

typedef struct {
    String key;
    bool used;
    u8 value[];
} MapEntry;

#define entry_size(data_size) (sizeof(MapEntry) - 1 + size)

static usize hash(const String str) {
    // FNV 32-bit hash
    unsigned int h = 2166136261;
    for (usize i = 0; i < str.len; i += 1) {
        h = h ^ ((u8)*(str.data + i));
        h = h * 16777619;
    }

    return h;
}

static MapHeader* get_header(const void* const map) {
    return (MapHeader*)((u8*)map - sizeof(MapHeader));
}

static void resize(void** map, MapHeader** header, usize size, usize new_cap) {
    usize old_cap = (*header)->cap;
    *header = realloc(*header, sizeof(MapHeader) + entry_size(size) * new_cap);
    (*header)->cap = new_cap;
    
    *map = (u8*)*header + sizeof(MapHeader);

    if (new_cap > old_cap) {
        memset(
            (u8*)*map + entry_size(size) * old_cap,
            0,
            entry_size(size) * (new_cap - old_cap)
        );
    }

}

void* map_init(void) {
    MapHeader* header = malloc(sizeof(MapHeader));

    header->cap = 0;
    header->len = 0;

    return (u8*)header + sizeof(MapHeader);
}

void map_deinit(void* map) {
    free((u8*)map - sizeof(MapHeader));
}

usize map_len(void* map) {
    MapHeader* header = get_header(map);

    return header->len;
}

void internal__map_insert(
    void** const map,
    const usize size,
    const String key,
    void* const value
) {
    MapHeader* header = get_header(*map);

    // resize if map reaches 80% capacity
    if (header->len * 5 >= header->cap * 4) {
        resize(map, &header, size, header->cap * 2 + 8);
    }

    usize start_index = hash(key);

    for (usize i = 0; i < header->cap; i += 1) {
        usize index = (start_index + i) % header->cap;

        MapEntry* entry = (MapEntry*)((u8*)*map + entry_size(size) * index);

        if (not entry->used or str_eq(entry->key, key)) {
            // increase size if this was empty
            header->len += not entry->used;
            entry->used = true;
            entry->key = key;

            memcpy(entry->value, value, size);

            break;
        }
    }
}

void* internal__map_get(
    const void* const map,
    const usize size,
    const String key
) {
    MapHeader* header = get_header(map);
    usize start_index = hash(key);

    for (usize i = 0; i < header->cap; i += 1) {
        usize index = (start_index + i) % header->cap;
        MapEntry* entry = (MapEntry*)((u8*)map + entry_size(size) * index);

        if (entry->used and str_eq(entry->key, key)) {
            return entry->value;
        }
    }

    return null;
}
