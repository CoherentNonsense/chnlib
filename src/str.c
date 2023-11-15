#include "str.h"

String str_init(const usize len) {
    char* ptr = malloc(sizeof(char) * len);

    return (String){ ptr, len };
}

void str_deinit(String str) {
    free(str.ptr);
}

String str_slice(char* ptr, const usize len) {
    return (String){ ptr, len };
}

bool str_eq(const String a, const String b) {
    if (a.len != b.len) { return false; }

    for (usize i = 0; i < a.len; i += 1) {
        if (a.ptr[i] != b.ptr[i]) { return false; }
    }

    return true;
}
