#include "defer.h"

bool _Thread_local defer_running = false;
void _Thread_local* defer_done_label_ptr = null;
void _Thread_local* defer_label_stack[32];
usize _Thread_local defer_label_stack_len = 0;
