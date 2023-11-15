#ifndef CHN_MAYBE_H
#define CHN_MAYBE_H

#include "chntype.h"


#define Maybe(T) T*

#define Some(expr) __extension__                                        \
({                                                                      \
    __typeof__(expr)* maybe = malloc(sizeof(expr));/*mem_alloc(global_allocator, sizeof(expr));*/\
    *maybe = expr;                                                      \
    maybe;                                                              \
})

#define None null

#define try(maybe) __extension__        \
({                                      \
    if (maybe == None) { return None; } \
    __typeof__(*maybe) val = *maybe;    \
    /*mem_free(global_allocator, expr);*/\
    free(maybe);                        \
    val;                                \
})

#endif
