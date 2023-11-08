#include "dynarray.h"
#include "logger.h"

#include <assert.h>


int main(void) {

    chn_info("testing dynarray_push");

    {
        DynArray(u32) array = dynarray_init();

        dynarray_push(array, &(u32){1});
        dynarray_push(array, &(u32){2});
        dynarray_push(array, &(u32){3});
        dynarray_push(array, &(u32){4});
        dynarray_push(array, &(u32){5});

        assert(array[3] == 4 and "dynarray_push");
        assert(dynarray_len(array) == 5 and "dynarray_push (len)");

        dynarray_deinit(array);
    }

    chn_info("testing dynarray_push (SUCCESS)");

    chn_info("testing dynarray_add");

    {
        DynArray(u32) array = dynarray_init();

        dynarray_add(array);
        dynarray_add(array);
        dynarray_add(array);
        dynarray_add(array);

        array[0] = 42;
        array[2] = 69;

        assert(array[2] == 69 and "dynarray_add");
        assert(dynarray_len(array) == 4 and "dynarray_add (len)");

        dynarray_deinit(array);
    }

    chn_info("testing dynarray_add (SUCCESS)");
}
