#include "map.h"

#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include <stdalign.h>
#include <stddef.h>


typedef struct {
    String key;
    bool used;
    alignas(max_align_t) u8 value[];
} MapEntry;

typedef struct {
    usize cap;
    usize len;
    u8 data[];
} MapHeader;

#define entry_size(data_size) (offsetof(MapEntry, value) + size)

static usize hash(const String str) {
    // FNV 32-bit hash
    unsigned int h = 2166136261;
    for (usize i = 0; i < str.len; i += 1) {
        h = h ^ ((u8)*(str.data + i));
        h = h * 16777619;
    }

    return h;
}

static void resize(void** map, usize size, usize new_cap) {
    MapHeader* header = (MapHeader*)(*map);

    usize old_cap = header->cap;
    header->cap = new_cap;

    *map = realloc(header, offsetof(MapHeader, data) + entry_size(size) * new_cap);
    header = (MapHeader*)*map;
   
    // clear any new entries
    if (new_cap > old_cap) {
        memset(
            header->data + entry_size(size) * old_cap,
            0,
            entry_size(size) * (new_cap - old_cap)
        );
    }
}

void* map_init(void) {
    MapHeader* header = malloc(sizeof(MapHeader));

    header->cap = 0;
    header->len = 0;

    return header;
}

void map_deinit(void* map) {
    free(map);
}

usize map_len(void* map) {
    MapHeader* header = (MapHeader*)map;

    return header->len;
}

void internal__map_insert(
    void** const map,
    const usize size,
    const String key,
    void* const value
) {
    MapHeader* header = (MapHeader*)(*map);

    // resize if map reaches 80% capacity
    if (header->len * 5 >= header->cap * 4) {
        resize(map, size, header->cap * 2 + 8);
        header = (MapHeader*)*map;
    }

    usize start_index = hash(key);
    for (usize i = 0; i < header->cap; i += 1) {
        usize index = (start_index + i) % header->cap;

        MapEntry* entry = (MapEntry*)(header->data + entry_size(size) * index);

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
    MapHeader* header = (MapHeader*)map;

    usize start_index = hash(key);
    for (usize i = 0; i < header->cap; i += 1) {
        usize index = (start_index + i) % header->cap;
        MapEntry* entry = (MapEntry*)(header->data + entry_size(size) * index);

        if (entry->used and str_eq(entry->key, key)) {
            return entry->value;
        }
    }

    return null;
}

MapIter internal__map_iter(const void* const map) {
    MapEntry* entry = (MapEntry*)map;

    // starts one entry back so we can call map_next first
    MapIter iter = (MapIter){ 0, entry };

    return iter;
}

bool internal__map_next(const void* map, const usize size, MapIter* iter) {
    MapHeader* header = (MapHeader*)map;

    while (true) {
        if (iter->index >= header->cap) { return false; }

        MapEntry* entry = (MapEntry*)(header->data + entry_size(size) * iter->index);
        iter->index += 1;

        if (not entry->used) {
            continue;
        }

        iter->entry = entry;
        return true;
    }
}

void* internal__map_iter_val(MapIter iter) {
    return ((MapEntry*)iter.entry)->value;
}
