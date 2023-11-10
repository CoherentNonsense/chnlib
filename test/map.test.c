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
        assert(map_get(map, str_from_lit("hellow")).b == 'd' and "map_get");


        chn_info("testing mutating data");
        TestData* ref = map_get_ref(map, str_from_lit("<-->"));
        ref->b = 'y';

        assert(map_get(map, str_from_lit("<-->")).b == 'y');
    }


    {
        chn_info("testing duplicates");
        
        Map(usize) map = map_init();
        map_insert(map, str_from_lit("a"), &(usize){42});
        map_insert(map, str_from_lit("a"), &(usize){69});
        map_insert(map, str_from_lit("a"), &(usize){0xC04});

        assert(map_get(map, str_from_lit("a")) == 0xC04 and "map_get");


        // keys from 'aaa' to 'zzz'
        chn_info("testing lots of entries");
        for (usize i = 0; i < 26 * 26 * 26; i += 1) {
            String key = str_init(3);
            key.data[0] = 'a' + i % 26;
            key.data[1] = 'a' + i / 26 % 26;
            key.data[2] = 'a' + i / (26 * 26) % 26;

            map_insert(map, key, &i);
        }

        assert(map_get(map, str_from_lit("aaa")) == 0 and "map_get(\"aaa\")");
        assert(map_get(map, str_from_lit("chn")) == 8972 and "map_get(\"chn\")");
        assert(map_get(map, str_from_lit("zzz")) == 26 * 26 * 26 - 1 and "map_get(\"zzz\")");
    }

    chn_info("testing map (SUCCESS)");
}
