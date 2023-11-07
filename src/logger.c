#include "logger.h"

#include <stdio.h>
#include <stdarg.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[92m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

typedef struct {
    ChnLogLevel log_level;
} ChnLogger;

static ChnLogger logger;
static char* LOG_LEVEL_DISPLAY[] = {  "DEBUG", "INFO", "WARNING", "ERROR" };
static char* LOG_LEVEL_COLOR[] =   {   BLUE,    GREEN,  YELLOW,    RED    };

void internal__chn_log(
    const ChnLogLevel level,
    const usize line_number,
    const char* const file_name,
    const char* const format,
    ...
) {
    if (level < logger.log_level) { return; }

    fprintf(stderr, "%s[%s %s:%zu] " RESET, LOG_LEVEL_COLOR[level], LOG_LEVEL_DISPLAY[level], file_name, line_number);

    // print formatted string
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");
}
