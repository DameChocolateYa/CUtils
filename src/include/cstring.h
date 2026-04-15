#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *data;
    size_t size;
    bool is_membusy;
} CString;

// Basic
extern CString cstring_new();
extern CString cstring_fromstr(const char *src);
extern void cstring_set_str(CString *string, const char *src);
extern CString cstring_clone(CString string);
extern void cstring_clear(CString *string);
extern size_t cstring_find(CString s1, const char *s2);
extern void cstring_cat(CString *string, const char *s2);
extern void cstring_merge(CString *s1, CString s2);
extern void cstring_cutpos(CString *s1, int begin, int end);
extern void cstring_cutstr(CString *s1, const char *substr);
extern char *cstring_substr(CString string, int begin, int end);
extern void cstring_repl(CString *string, const char *old, const char *new);
extern void cstring_fmt(CString *string, ...);
extern void cstring_newfmt(CString *string, const char *fmt, ...);
extern void cstring_ask(CString *string, ...);
extern void cstring_newask(CString *string, const char *fmt, ...);
extern void cstring_destroy(CString *string);
extern char *cstring_str(CString string);
extern bool cstring_isempty(CString string);

// Other stuff
extern void cstring_upper(CString *string);
extern void cstring_lower(CString *string);
extern void cstring_swap(CString *string, size_t b1, size_t e1, size_t b2, size_t e2);

#endif