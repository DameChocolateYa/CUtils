#ifndef STRING_H
#define STRING_H

#include <stdlib.h>

typedef struct {
    char *data;
    size_t size;
    bool is_membusy;
} CString;

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
extern void cstring_delete(CString *string);
extern char *cstring_str(CString string);

#endif