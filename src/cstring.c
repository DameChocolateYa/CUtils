#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
        perror("Could not create String\n");
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
        perror("from_str: Could not make a correct allocation for string\n");
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
        perror("Could not reallocate memory for String\n");
        return;
    }
    
    strcpy(string->data, src);
}

CString cstring_clone(CString string) {
    if (!string.data || !string.mem_busy) {
        perror("Could not clone string\n");
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
    
    string->data = realloc(string->data, string->size + strlen(s2));
    if (!string->data) {
        perror("Could not reallocate memory for string concatenation\n");
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
        perror("Could not reallocate memory for string concatenation\n");
        return;
    }

    strcpy(s1->data + s1->size, s2.data);
    s1->size += s2.size;
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
        perror("cut_string_pos: Could not reallocate memory for string\n");
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
