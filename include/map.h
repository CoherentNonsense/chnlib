#ifndef CHN_MAP_H
#define CHN_MAP_H

#include "chntype.h"
#include "str.h"
#include "maybe.h"


#define Map(T) T*

void* map_init(void);
void map_deinit(void* map);

usize map_len(void* map);

void internal__map_insert(void** const map, const usize size, const String key, void* const value);
#define map_insert(map, key, value) do { \
    __typeof__(map) tmp = value;         \
    internal__map_insert(                \
        (void**)&map,                    \
        sizeof(*map),                    \
        key,                             \
        tmp                              \
    );                                   \
} while(0)

void* internal__map_get(const void* const map, const usize size, const String key);
#define map_get(map, key) __extension__ \
({ \
    __typeof__(map) ref = internal__map_get(map, sizeof(*map), key); \
    ref == null ? None : Some(*ref); \
})
#define map_get_ref(map, key) ((__typeof__(map))internal__map_get(map, sizeof(*map), key))

typedef struct {
    usize index;
    void* entry;
} MapIter;

MapIter internal__map_iter(const void* const map);
#define map_iter(map) internal__map_iter(map)

bool internal__map_next(const void* map, const usize size, MapIter* iter);
#define map_next(map, iter) internal__map_next(map, sizeof(*map), (MapIter*)&iter)

void* internal__map_iter_val(MapIter iter);
#define map_iter_val(map, iter) (*(__typeof__(map))internal__map_iter_val(iter))
#define map_iter_val_ref(map, iter) ((__typeof__(map))internal__map_iter_val(iter))

#endif
