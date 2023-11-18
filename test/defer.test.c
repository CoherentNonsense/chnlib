#include "defer.h"

#include "stdio.h"
#include "dynarray.h"

void hello(void) {
    puts("Hello!");
}

void goodbye(void) {
    puts("Goodbye!");
}

i32 main(void) {
    hello();
    defer (goodbye());

    puts("How are you?");

    defer_return (0);
}
