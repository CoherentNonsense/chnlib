#ifndef CHN_DEFER_H
#define CHN_DEFER_H

#include "chntype.h"

_Thread_local extern bool defer_running;
_Thread_local extern void* defer_done_label_ptr;
_Thread_local extern void* defer_label_stack[32];
_Thread_local extern usize defer_label_stack_len;
_Thread_local extern void* defer_errlabel_stack[32];
_Thread_local extern usize defer_errlabel_stack_len;

void internall__defer_push(void);
void internall__defer_pop(void);


#define defer(expr) internal__defer_(__COUNTER__, expr)
#define internal__defer_(num, expr) internal__defer(num, expr)
#define internal__defer(num, expr)                                       \
do {                                                            \
    defer_expr_label##num:                                      \
    if (defer_running) {                                        \
        expr;                                                   \
        if (defer_label_stack_len > 0) {                        \
            goto *defer_label_stack[--defer_label_stack_len];   \
        } else {                                                \
            goto *defer_done_label_ptr;                         \
        }                                                       \
    } else {                                                    \
        defer_label_stack[defer_label_stack_len++] =            \
            &&defer_expr_label##num;                            \
    }                                                           \
} while(0)

#define errdefer(expr) internal__errdefer_(__COUNTER__, expr)
#define internal__errdefer_(num, expr) internal__errdefer(num, expr)
#define internal__errdefer(num, expr) \
do { \
    defer_expr_label##num: \
    expr; \
    if (defer_running) { \
        if (defer_errlabel_stack_len > 0) { \
            goto *defer_errlabel_stack[--defer_errlabel_stack_len];     \
        } else if (defer_label_stack_len > 0) { \
            goto *defer_label_stack[--defer_label_stack_len]; \
        } else { \
            goto *defer_done_label_ptr; \
        } \
    } else { \
        defer_errlabel_stack[defer_errlabel_stack_len++] =      \
            &&defer_expr_label##num; \
    } \
} while(0)

#define defer_return internal__defer_return_(__COUNTER__)
#define internal__defer_return_(num) internal__defer_return(num)
#define internal__defer_return(num) do {          \
    defer_running = true;                               \
    defer_done_label_ptr = &&defer_done_label##num;     \
    if (defer_label_stack_len > 0) {                    \
        goto *defer_label_stack[--defer_label_stack_len]; \
    }                           \
    defer_done_label##num:      \
    defer_running = false;      \
} while(0); return

#define defer_error internal__defer_error_(__COUNTER__)
#define internal__defer_error_(num) internal__defer_error(num)
#define internal__defer_error(num) do { \
    defer_running = true; \
    defer_done_label_ptr = &&defer_done_label##num; \
    if (defer_errlabel_stack_len > 0) { \
        goto *defer_errlabel_stack[--defer_errlabel_stack_len];     \
    } else if (defer_label_stack_len > 0) { \
        goto *defer_label_stack[--defer_label_stack_len]; \
    } \
    defer_done_label##num: \
    defer_running = false; \
} while(0); return

#endif
