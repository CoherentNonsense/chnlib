#ifndef CHN_STRBUFFER_H
#define CHN_STRBUFFER_H

#include "chntype.h"
#include "str.h"


typedef struct StrBufferFragment {
    struct StrBufferFragment* next;
    usize len;
    char data[];
} StrBufferFragment;

typedef struct {
    StrBufferFragment* start;
    StrBufferFragment* cur;
    usize len;
} StrBuffer;

StrBuffer strbuf_init(void);
void strbuf_deinit(StrBuffer* strbuf);

// frees memory so you shouldn't call strbuf_deinit afterwards
String strbuf_to_string(StrBuffer* strbuf);

__attribute__((format(printf, 2, 3)))
void strbuf_printf(StrBuffer* strbuf, const char* format, ...);
void strbuf_print_str(StrBuffer* strbuf, String string);
#define strbuf_print_lit(strbuf, lit) strbuf_print_str(strbuf, str_from_lit(lit))


#endif
