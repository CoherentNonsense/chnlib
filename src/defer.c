#include "defer.h"

_Thread_local bool defer_running = false;
_Thread_local void* defer_done_label_ptr = null;
_Thread_local void* defer_label_stack[32];
_Thread_local usize defer_label_stack_len = 0;
_Thread_local void* defer_errlabel_stack[32];
_Thread_local usize defer_errlabel_stack_len = 0;
