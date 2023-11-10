#include "str.h"

String str_init(const usize len) {
    char* data = malloc(sizeof(char) * len);

    return (String){ data, len };
}

void str_deinit(String str) {
    free(str.data);
}

String str_slice(char* data, const usize len) {
    return (String){ data, len };
}

bool str_eq(const String a, const String b) {
    if (a.len != b.len) { return false; }

    for (usize i = 0; i < a.len; i += 1) {
        if (a.data[i] != b.data[i]) { return false; }
    }

    return true;
}
