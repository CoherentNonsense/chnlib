#include "maybe.h"

#include "logger.h"
#include <assert.h>


static Maybe(i32) maybe_null(i32 input) {
    if (input > 100) {
        return None;
    }

    i32 result = input + 10;

    return Some(result);
}

Maybe(i32) driver(i32 start) {
    i32 a = try(maybe_null(start));
    i32 b = try(maybe_null(a));
    i32 c = try(maybe_null(b));
    i32 d = try(maybe_null(c));

    return Some(d);
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
