#include "str.h"

#include "logger.h"
#include <assert.h>


int main(void) {
    chn_info("testing string");

    {
        chn_info("testing string slice");
        String a = str_from_lit("hello");
        String a_slice = str_slice(a.data, a.len);

        assert(str_eq(a, a_slice) and "string is the same as slice");
    }

    {
        chn_info("testing string allocation");
        String a = str_from_lit("chn");
        String b = str_init(3);
        b.data[0] = 'c';
        b.data[1] = 'h';
        b.data[2] = 'n';

        assert(str_eq(a, b) and "null terminated is same as non null terminated");

        str_deinit(b);
    }

    chn_info("testing string (SUCCESS)");

    return 0;
}
