#ifndef CHN_MAYBE_H
#define CHN_MAYBE_H

#include "chntype.h"


#define MAX_MAYBE_VALUE 128

#define Maybe(T) T*

extern u8 internal__maybe_value[MAX_MAYBE_VALUE];

#define Some(expr) __extension__                                \
({                                                              \
    __typeof__(expr)* maybe = (void*)internal__maybe_value;     \
    *maybe = expr;                                              \
    maybe;                                                      \
})

#define None null

#define try(maybe_expr) __extension__           \
({                                              \
    __typeof__(maybe_expr) maybe = maybe_expr;  \
    if (maybe == None) { return None; }         \
    *maybe;                                     \
})

#define unwrap(maybe) (*maybe)

#endif
