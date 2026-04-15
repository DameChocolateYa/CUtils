#ifndef CRITICAL_H
#define CRITICAL_H

#include <stdarg.h>

char *strbuf(const char *fmt, int *len_r, va_list args);

#endif