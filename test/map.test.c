#include "map.h"

#include "logger.h"
#include <assert.h>

typedef struct {
    u64 a;
    char b;
    u16 c;
} TestData;

int main(void) {

    chn_info("testing map");

    {
        chn_info("testing map_insert");

        Map(TestData) map = map_init();
        map_insert(map, str_from_lit("a"), &((TestData){ .b='a' }));
        map_insert(map, str_from_lit("hellow"), &((TestData){ .b='d' }));
        map_insert(map, str_from_lit(":^)"), &((TestData){ .b='b' }));
        map_insert(map, str_from_lit("this is a key"), &((TestData){ .b='f' }));
        map_insert(map, str_from_lit("A"), &((TestData){ .b='z' }));
        map_insert(map, str_from_lit("<-->"), &((TestData){ .b='x' }));

        assert(map_len(map) == 6 and "map_len");

        assert(map_get_ref(map, str_from_lit("this is a key"))->b == 'f' and "map_get_ref");
        assert(unwrap(map_get(map, str_from_lit("hellow"))).b == 'd' and "map_get");


        chn_info("testing mutating data");
        TestData* ref = map_get_ref(map, str_from_lit("<-->"));
        ref->b = 'y';

        assert(unwrap(map_get(map, str_from_lit("<-->"))).b == 'y');

        map_deinit(map);
    }

    {
        chn_info("testing nonexisting entry");

        Map(usize) map = map_init();

        map_insert(map, str_from_lit("a"), &(usize){42});

        assert(map_get(map, str_from_lit("b")) == None and "nonexistant is null");

        map_deinit(map);
    }

    {
        chn_info("testing duplicates");
        
        Map(usize) map = map_init();
        map_insert(map, str_from_lit("a"), &(usize){42});
        map_insert(map, str_from_lit("a"), &(usize){69});
        map_insert(map, str_from_lit("a"), &(usize){0xC04});

        assert(unwrap(map_get(map, str_from_lit("a"))) == 0xC04 and "map_get");


        // keys from 'aaa' to 'zzz'
        chn_info("testing lots of entries");
        // TODO: remove this when i use an allocator
        String* keys = malloc(sizeof(String) * 26 * 26 * 26);
        for (usize i = 0; i < 26 * 26 * 26; i += 1) {
            keys[i] = str_init(3);
            keys[i].ptr[0] = 'a' + i % 26;
            keys[i].ptr[1] = 'a' + i / 26 % 26;
            keys[i].ptr[2] = 'a' + i / (26 * 26) % 26;

            map_insert(map, keys[i], &i);
        }

        assert(unwrap(map_get(map, str_from_lit("aaa"))) == 0 and "map_get(\"aaa\")");
        assert(unwrap(map_get(map, str_from_lit("chn"))) == 8972 and "map_get(\"chn\")");
        assert(unwrap(map_get(map, str_from_lit("zzz"))) == 26 * 26 * 26 - 1 and "map_get(\"zzz\")");

        for (usize i = 0; i < 26 * 26 * 26; i += 1) {
            str_deinit(keys[i]);
        }
        free(keys);

        map_deinit(map);
    }

    {
        chn_info("testing iterator");

        Map(usize) map = map_init();
        map_insert(map, str_from_lit("a"), &(usize){10});
        map_insert(map, str_from_lit("b"), &(usize){11});
        map_insert(map, str_from_lit("c"), &(usize){12});
        map_insert(map, str_from_lit("d"), &(usize){13});
        map_insert(map, str_from_lit("e"), &(usize){14});

        MapIter iter = map_iter(map);
        usize found = 0;
        while (map_next(map, iter)) {
            found += 1;
            usize val = map_iter_val(map, iter);
            chn_info("map entry %zu: %zu", iter.index, val);
            assert((10 <= val and val <= 14) and "map_iter_val");
        }

        assert(found == 5 and "all values iterated over");

        map_deinit(map);
    }

    chn_info("testing map (SUCCESS)");
}
