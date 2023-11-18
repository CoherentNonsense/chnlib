#ifndef CHN_DEFER_H
#define CHN_DEFER_H

#include "chntype.h"

extern _Thread_local bool defer_running;
extern _Thread_local void* defer_done_label_ptr;
extern _Thread_local void* defer_label_stack[32];
extern _Thread_local usize defer_label_stack_len;

void internall__defer_push(void);
void internall__defer_pop(void);

#define fn(name, ret_type) ret_type name

#define defer(expr)                                             \
do {                                                            \
    __label__ defer_expr_label;                                 \
    defer_expr_label:                                           \
    if (defer_running) {                                        \
        expr;                                                   \
        if (defer_label_stack_len > 0) {                        \
            goto *defer_label_stack[--defer_label_stack_len];   \
        } else {                                                \
            goto *defer_done_label_ptr;                         \
        }                                                       \
    } else {                                                    \
        defer_label_stack[defer_label_stack_len++] =            \
            &&defer_expr_label;                                 \
    }                                                           \
} while(0)

#define defer_return(expr) do {                         \
    __label__ defer_done_label;                         \
    defer_running = true;                               \
    defer_done_label_ptr = &&defer_done_label;          \
    if (defer_label_stack_len > 0) {                    \
        goto *defer_label_stack[--defer_label_stack_len]; \
    }                           \
    defer_done_label:           \
    defer_running = false;      \
    return (expr);              \
} while(0)

#endif
