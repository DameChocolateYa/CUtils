#include "../include/CMath.h"
#include <stdarg.h>

int CMT_SumI32(int count, ...) {
    va_list args;

    va_start(args, count);

    int n = 0;
    for (int i = 0; i < count; i++) {
        n += va_arg(args, int);
    }

    va_end(args);
    return n;
}

int CMT_SubI32(int count, ...) {
    va_list args;

    va_start(args, count);

    int n = va_arg(args, int);
    for (int i = 1; i < count; i++) {
        n -= va_arg(args, int);
    }

    va_end(args);
    return n;
}

int CMT_MulI32(int count, ...) {
    va_list args;

    va_start(args, count);

    int n = 1;
    for (int i = 0; i < count; i++) {
        n *= va_arg(args, int);
    }

    va_end(args);
    return n;
}