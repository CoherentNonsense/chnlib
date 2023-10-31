#include "logger.h"

int main(void) {
    chn_info("Hello, %s!", "World");
    chn_warning("Number detected: %d", 42);
    chn_error("Stop right there!");

    return 0;
}
