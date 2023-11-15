#include "strbuffer.h"

#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


StrBuffer strbuf_init(void) {
    return (StrBuffer){
        .start = null,
        .cur = null,
    };
}

void strbuf_deinit(StrBuffer* strbuf) {
    while (strbuf->start != null) {
        StrBufferFragment* tmp = strbuf->start;
        strbuf->start = tmp->next;
        free(tmp);
    }
}

String strbuf_to_string(StrBuffer* strbuf) {
    char* ptr = malloc(strbuf->len);
    usize offset = 0;

    while (strbuf->start != null) {
        StrBufferFragment* tmp = strbuf->start;
        strbuf->start = tmp->next;

        memcpy(ptr + offset, tmp->data, tmp->len);
        offset += tmp->len;

        free(tmp);
    }

    return str_slice(ptr, strbuf->len);
}

__attribute__((format(printf, 2, 3)))
void strbuf_printf(StrBuffer* strbuf, const char* format, ...) {
    char buffer[1024];

    va_list args;
    va_start(args, format);

    int buffer_len = vsnprintf(buffer, 1024, format, args);

    va_end(args);

    if (buffer_len < 0) { return; }

    strbuf_print_str(strbuf, str_slice(buffer, buffer_len));
}

void strbuf_print_str(StrBuffer* strbuf, String str) {
    StrBufferFragment* frag = malloc(offsetof(StrBufferFragment, data) + str.len);

    frag->len = str.len;
    frag->next = null;
    memcpy(frag->data, str.ptr, frag->len);

    strbuf->len += frag->len;

    if (strbuf->start == null) {
        strbuf->start = frag;
    } else {
        strbuf->cur->next = frag;
    }

    strbuf->cur = frag;
}
