#ifndef CHN_LOGGER_H
#define CHN_LOGGER_H

#include "chntype.h"

typedef enum {
    Chn_LogLevel_Debug,
    Chn_LogLevel_Info,
    Chn_LogLevel_Warning,
    Chn_LogLevel_Error,
} ChnLogLevel;

__attribute__((format(printf, 4, 5)))
void internal__chn_log(
    const ChnLogLevel level,
    const usize line_number,
    const char* const file_name,
    const char* const format,
    ...
);

#define chn_debug(format, ...) internal__chn_log(Chn_LogLevel_Debug, __LINE__, __FILE__, format __VA_OPT__(,) __VA_ARGS__)
#define chn_info(format, ...) internal__chn_log(Chn_LogLevel_Info, __LINE__, __FILE__, format __VA_OPT__(,) __VA_ARGS__)
#define chn_warning(format, ...) internal__chn_log(Chn_LogLevel_Warning, __LINE__, __FILE__, format __VA_OPT__(,) __VA_ARGS__)
#define chn_error(format, ...) internal__chn_log(Chn_LogLevel_Error, __LINE__, __FILE__, format __VA_OPT__(,) __VA_ARGS__)

#endif
