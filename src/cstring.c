#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include "include/critical.h"

typedef struct {
    char *data; // main string with memory allocation
    size_t size; // NEVER includes null terminator
    bool mem_busy; // == data
} CString;

CString cstring_new() {
    CString string;
    string.data = malloc(1);
    string.size = 0;
    
    if (!string.data) {
        fprintf(stderr, "Could not create String\n");
        return (CString) {NULL, 0};
    }
    
    string.mem_busy = true;
    
    return string;
}

CString cstring_fromstr(const char *src) {
    CString string = cstring_new();
    if (!string.data)
        return string; // The error comes from new_string, no need to put it again
    
    string.data = realloc(string.data, strlen(src) + 1);
    if (!string.data || !string.mem_busy) {
        fprintf(stderr, "from_str: Could not make a correct allocation for string\n");
        return string;
    }
    
    strcpy(string.data, src);
    string.size = strlen(src);
    
    return string;
}

void cstring_set_str(CString *string, const char *src) {
    if (!string->data || !string->mem_busy || !src) {
        return;
    }
    
    strcpy(string->data, "");
    string->data = realloc(string->data, strlen(src));
    
    if (!string->data) {
        fprintf(stderr, "Could not reallocate memory for String\n");
        return;
    }
    
    strcpy(string->data, src);
}

CString cstring_clone(CString string) {
    if (!string.data || !string.mem_busy) {
        fprintf(stderr, "Could not clone string\n");
        return (CString){NULL, 0};
    }
    
    CString cloned = cstring_fromstr(string.data);
    return cloned;
}

void cstring_clear(CString *string) {
    if (!string->data || !string->mem_busy)
        return;
    
    strcpy(string->data, "");
    string->size = 0;
}

size_t cstring_find(CString s1, const char *s2) {
    size_t n = s1.size;
    size_t m = strlen(s2);

    if (m > n) return -1;

    for (size_t i = 0; i <= n - m; i++) {
        size_t j = 0;
        for (; j < m; j++) {
            if (s1.data[i + j] != s2[j]) break;
        }
        if (j == m) return (size_t)i;
    }

    return -1;
}

void cstring_cat(CString *string, const char *s2) {
    if (!string->data || !string->mem_busy || !s2)
        return;
    
    size_t new_size = string->size + strlen(s2);
    new_size = new_size == 0 ? 1 : new_size; // data requires at least 1 byte for comprobation
    string->data = realloc(string->data, new_size);
    if (!string->data) {
        pfprintf(stderr, "Could not reallocate memory for string concatenation\n");
        return;
    }
    
    strcpy(string->data + string->size, s2);
    string->size += strlen(s2);
}

void cstring_merge(CString *s1, CString s2) {
    if (!s1->data || !s1->mem_busy || !s2.data || !s2.mem_busy) {
        return;
    }

    s1->data = realloc(s1->data, s1->size + s2.size);
    if (!s1->data) {
        fprintf(stderr, "Could not reallocate memory for string concatenation\n");
        return;
    }

    strcpy(s1->data + s1->size, s2.data);
    s1->size += s2.size;
    s1->data[s1->size + 1] = '\0';
}

void cstring_cutpos(CString *string, int begin, int end) {
    if (!string->data || !string->mem_busy)
        return;
    
    int new_size = string->size - (end - begin);

    memmove(string->data + begin,
        string->data + end,
        string->size - end + 1);
    string->data = realloc(string->data, new_size + 1);
    if (!string->data) {
        fprintf(stderr, "cut_string_pos: Could not reallocate memory for string\n");
        return;
    }

    string->size = new_size;
    string->data[string->size] = '\0';
}

void cstring_cutstr(CString *string, const char *substr) {
    int loc = cstring_find(*string, substr);
    if (loc < 0) return;

    size_t len = strlen(substr);

    memmove(string->data + loc, string->data + loc + len, string->size - (loc + len));
    string->size -= len;
    string->data = realloc(string->data, string->size + 1);

    string->data[string->size] = '\0';
}

char *cstring_substr(CString string, int begin, int end) {
    if (begin > end) {
        int temp = begin;
        begin = end;
        end = temp;
    }

    if (begin < 0 || end > string.size) {
        return NULL;
    }

    int lenght = end - begin + 1;
    char *s = malloc(lenght);
    for (int i = 0; i < lenght; i++) {
        s[i] = string.data[begin + i];
    }
    s[lenght] = '\0';

    return s;
}

CString cstring_sub(CString string, int begin, int end) {
    if (begin > end) {
        int temp = begin;
        begin = end;
        end = temp;
    }

    if (begin < 0 || end > string.size) {
        return (CString){NULL, 0};
    }

    int lenght = end - begin + 1;
    char *s = malloc(lenght + 1);
    for (int i = 0; i < lenght; i++) {
        s[i] = string.data[begin + i];
    }
    s[lenght] = '\0';

    CString new_string = cstring_fromstr(s);
    free(s);

    return new_string;
}

void cstring_destroy(CString *string);
void cstring_repl(CString *string, const char *old, const char *new) {
    int loc = cstring_find(*string, old);
    if (loc == -1) return;

    CString after = cstring_sub(*string, loc + strlen(old), string->size);
    cstring_cutpos(string, loc, string->size);
    cstring_cat(string, new);
    cstring_merge(string, after);

    cstring_destroy(&after);
}

void cstring_fmt(CString *string, ...) {
    va_list args;
    va_start(args, string);

    int len;
    char *s = strbuf(string->data, &len, args);

    va_end(args);

    free(string->data);
    string->size = len;
    string->data = malloc(string->size + 1);
    strcpy(string->data, s);
    string->data[string->size + 1] = '\0';
}

void cstring_newfmt(CString *string, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int len; // strbuf requires it by default
    char *s = strbuf(fmt, &len, args);

    va_end(args);

    free(string->data);
    string->size = len;
    string->data = malloc(string->size + 1);
    strcpy(string->data, s);
    string->data[string->size + 1] = '\0';
}

void cstring_newask(CString *string, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int len;
    char *s = strbuf(fmt, &len, args);

    va_end(args);

    printf(s);
    free(s);

    char *ret = malloc(120);
    scanf("%120s", ret);

    ret = realloc(ret, strlen(ret) + 1);
    
    free(string->data);
    string->size = strlen(ret);
    string->data = ret;
    string->data[string->size + 1] = '\0';
}

void cstring_ask(CString *string, ...) {
    va_list args;
    va_start(args, string);

    int len;
    char *s = strbuf(string->data, &len, args);

    va_end(args);

    printf(s);
    free(s);

    char *ret = malloc(120);
    scanf("%120s", ret);
    
    ret = realloc(ret, strlen(ret) + 1);

    free(string->data);
    string->size = strlen(ret);
    string->data = ret;
    string->data[string->size + 1] = '\0';
}

void cstring_destroy(CString *string) {
    if (string->mem_busy) {
        free(string->data);
        string->size = 0;
    }
}

char *cstring_str(CString string) {
    if (!string.data || !string.mem_busy) {
        return "(null)";
    }
    
    return string.data;
}

bool cstring_isempty(CString string) {
    return !string.data || !string.mem_busy || string.size <= 0;
}

// Other non needed stuff for basic use
void cstring_upper(CString *string) {
    if (cstring_isempty(*string))
        return;
    
    for (size_t i = 0; string->data[i] != '\0'; i++) {
        if (string->data[i] >= 'a' && string->data[i] <= 'z') {
            string->data[i] -= 32;
        }
    }
}

void cstring_lower(CString *string) {
    if (cstring_isempty(*string))
        return;
    
    for (size_t i = 0; string->data[i] != '\0'; i++) {
        if (string->data[i] >= 'A' && string->data[i] <= 'Z') {
            string->data[i] += 32;
        }
    }
}

void cstring_swap(CString *string, size_t b1, size_t e1, size_t b2, size_t e2) {
    if (!string || b1 > e1 || b2 > e2 || e1 >= string->size || e2 >= string->size)
        return;

     if (b1 > b2) {
        size_t tb = b1, te = e1;
        b1 = b2; e1 = e2;
        b2 = tb; e2 = te;
    }
    
    const char *s1 = cstring_substr(*string, b1, e1);
    const char *s2 = cstring_substr(*string, b2, e2);

    const char *mid = (e1 + 1 < b2) ? cstring_substr(*string, e1 + 1, b2 - 1) : "";
    const char *prefix = (b1 > 0) ? cstring_substr(*string, 0, b1 - 1) : "";
    const char *suffix = (e2 + 1 < string->size) ? cstring_substr(*string, e2 + 1, string->size - 1) : "";

    CString new_string = cstring_new();

    cstring_cat(&new_string, prefix);
    cstring_cat(&new_string, s2);
    cstring_cat(&new_string, mid);
    cstring_cat(&new_string, s1);
    cstring_cat(&new_string, suffix);

    cstring_destroy(string);
    *string = new_string;

    free((void*)s1);
    free((void*)s2);
    if (mid[0]) free((void*)mid);
    if (prefix[0]) free((void*)prefix);
    if (suffix[0]) free((void*)suffix);
}