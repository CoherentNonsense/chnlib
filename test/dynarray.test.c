#include "dynarray.h"
#include "logger.h"

#include <assert.h>


typedef struct {
    u32 a;
    char* b;
    u16 c;
} TestData;

int main(void) {

    chn_info("testing dynarray_push");

    {
        DynArray(TestData) array = dynarray_init();

        dynarray_push(array, &((TestData){ .a=1 }));
        dynarray_push(array, &((TestData){ .a=2 }));
        dynarray_push(array, &((TestData){ .a=3 }));
        dynarray_push(array, &((TestData){ .a=4 }));
        dynarray_push(array, &((TestData){ .a=5 }));

        assert(array[3].a == 4 and "dynarray[n]");
        assert(dynarray_len(array) == 5 and "dynarray_len");

        dynarray_deinit(array);
    }

    chn_info("testing dynarray_push (SUCCESS)");

    chn_info("testing dynarray_add");

    {
        DynArray(TestData) array = dynarray_init();

        dynarray_add(array);
        dynarray_add(array);
        dynarray_add(array);
        dynarray_add(array);

        array[0].a = 42;
        array[2].a = 69;

        assert(array[2].a == 69 and "dynarray[n]");
        assert(dynarray_len(array) == 4 and "dynarray_len");

        dynarray_deinit(array);
    }

    chn_info("testing dynarray_add (SUCCESS)");

    chn_info("testing lots of data");

    {
        DynArray(usize) array = dynarray_init();

        for (usize i = 0; i < 500; i += 1) {
            dynarray_push(array, &(usize){i});
        }

        assert(array[100] == 100 and "dynarray[n]");
        assert(dynarray_len(array) == 500 and "dynarray_len");

        dynarray_deinit(array);
    }

    chn_info("testing lots of data (SUCCESS)");
}
