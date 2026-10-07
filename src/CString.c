#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/CString.h"

static void _cst_enlarge(struct cst_string *string) {
    string->data = realloc(string->data, string->capacity * 2);
    if (!string->data) {
        fprintf(stderr, "_cst_enlarge: could not reallocate memory for string enlargment\n");
        return;
    }
    string->capacity *= 2;
}

static void _cst_enlarge_cond(struct cst_string *string, size_t min) {
    while (min > string->capacity)
        _cst_enlarge(string);
}

size_t CST_StrLen(const char *s) {
    size_t i = 0;
    while (s[i++] != '\0');
    return --i;
}

CST_String CST_Create() {
    CST_String string;

    string.data = malloc(1);
    if (!string.data) {
        fprintf(stderr, "CST_Create: could not allocate memory for CST_String\n");
        return string;
    }

    string.length = 0;
    string.capacity = 1;
    return string;
}

void CST_Destroy(CST_String *string) {
    if (!string->data)
        return;
    
    free(string->data);
    string = NULL;
}

CST_String CST_From(const char *content) {
    CST_String string;

    string.data = malloc(CST_StrLen(content) + 1);
    if (!string.data || !content) {
        fprintf(stderr, "CST_From: could not allocate memory for CST_String\n");
        return string;
    }
    strcpy(string.data, content);
    string.length = CST_StrLen(content);
    string.capacity = string.length + 1;

    return string;
}

char *CST_AsStr(CST_String string) {
    if (!string.data)
        return "(null)";
    
    return string.data;
}

size_t CST_Len(CST_String string) {
    return string.length;
}

void CST_Set(CST_String *string, char *content) {
    _cst_enlarge_cond(string, CST_StrLen(content) + 1);
    strcpy(string->data, content);
    string->length = CST_StrLen(content);
}

void CST_Cat(CST_String *string, char *content) {
    _cst_enlarge_cond(string, string->length + CST_StrLen(content) + 1);
    strcat(string->data, content);
    string->length += CST_StrLen(content);
}