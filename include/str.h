#ifndef CHN_STRING_H
#define CHN_STRING_H

#include "chntype.h"

typedef struct {
    char* ptr;
    usize len;
} String;

String str_init(const usize len);
void str_deinit(String str);
String str_slice(char* ptr, const usize len);

// macro for comptime sizeof
#define str_from_lit(literal) (String){ literal, sizeof(literal) - 1 }

bool str_eq(const String a, const String b);

// to be used in formatted string. e.g. printf(".*s\n", str_format(foo));
#define str_format(str) (int)(str).len, (str).ptr

#endif
