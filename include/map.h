#ifndef CHN_MAP_H
#define CHN_MAP_H

#include "chntype.h"
#include "str.h"


#define Map(T) T*

void* map_init(void);
void map_deinit(void* map);

usize map_len(void* map);

#define map_insert(map, key, value) internal__map_insert((void**)&map, sizeof(*map), key, value);
void internal__map_insert(void** const map, const usize size, const String key, void* const value);

#define map_get(map, key) (*(__typeof__(map))internal__map_get(map, sizeof(*map), key))
#define map_get_ref(map, key) ((__typeof__(map))internal__map_get(map, sizeof(*map), key))
void* internal__map_get(const void* const map, const usize size, const String key);

#endif
