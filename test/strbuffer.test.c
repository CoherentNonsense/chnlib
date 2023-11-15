#include "strbuffer.h"

#include "logger.h"
#include <assert.h>


int main(void) {

    chn_info("testing string buffer");
    {
        StrBuffer strbuf = strbuf_init();
        strbuf_print_lit(&strbuf, "hello, ");
        strbuf_print_str(&strbuf, str_from_lit("there!"));

        String result = strbuf_to_string(&strbuf);

        assert(str_eq(result, str_from_lit("hello, there!")) and "printing string and literal");

        str_deinit(result);
    }

    {
        StrBuffer strbuf = strbuf_init();
        strbuf_printf(&strbuf, "this can be any%dthing\n", 39);
        strbuf_printf(&strbuf, "hopefully this %s", "works");

        String result = strbuf_to_string(&strbuf);

        assert(
            str_eq(result, str_from_lit("this can be any39thing\nhopefully this works"))
            and "printing formatted string"
        );

        str_deinit(result);
    }
    chn_info("testing string buffer (SUCCESS)");

    return 0;
}
