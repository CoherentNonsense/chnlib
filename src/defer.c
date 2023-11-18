#include "defer.h"

bool defer_running = false;
void* defer_done_label_ptr = null;
void* defer_label_stack[32];
usize defer_label_stack_len = 0;
