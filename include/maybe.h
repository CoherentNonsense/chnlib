#ifndef CHN_MAYBE_H
#define CHN_MAYBE_H

#include "chntype.h"

#define Maybe(expression) __extension__  \
({                                       \
    void* result = (void*)expression;    \
    if (result == null) { return null; } \
    result;                              \
})

#endif
