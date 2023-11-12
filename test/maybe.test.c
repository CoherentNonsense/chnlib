#include "maybe.h"

#include "logger.h"
#include <assert.h>


static i32* maybe_null(i32 input) {
    if (input > 100) {
        return null;
    }

    i32* ret = Maybe(malloc(sizeof(i32)));
    *ret = input + 10;

    return ret;
}

i32* driver(i32 start) {
    i32* a_ref = Maybe(maybe_null(start));
    // guarunteed non null value
    int a = *a_ref;
    free(a_ref);

    i32* b_ref = Maybe(maybe_null(a));
    int b = *b_ref;
    free(b_ref);

    i32* c_ref = Maybe(maybe_null(b));
    int c = *c_ref;
    free(c_ref);

    i32* d = Maybe(maybe_null(c));
    return d;
}

int main(void) {

    chn_info("testing Maybe(T)");

    {
        chn_info("testing none state");
        i32* result = driver(10);

        assert(result != null and "return non null value");
        assert(*result == 50 and "correct result");

        free(result);
    }

    {
        chn_info("testing some state");
        i32* result = driver(90);

        assert(result == null and "correct result");

        free(result);
    }

    chn_info("testing Maybe(T) (SUCCESS)");

    return 0;
}
