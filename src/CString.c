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

void CST_CatChar(CST_String *string, char c) {
    _cst_enlarge_cond(string, string->length + 2);
    string->data[string->length] = c;
    string->data[string->length + 1] = '\0';
    string->length++;
}

char CST_At(CST_String string, size_t index) {
    if (index < 0 || index > string.length) {
        fprintf(stderr, "CST_At: index out of range\n");
        return '\0';
    }

    return string.data[index];
}

void CST_Cut(CST_String *string, size_t begin, size_t end) {
    if (begin > end) {
        int temp = begin;
        begin = end;
        end = temp;
    }

    if (begin < 0 || end > string->length) {
        fprintf(stderr, "CST_Cut: index out of range");
        return;
    }

    CST_String ss = CST_Create();
    _cst_enlarge_cond(&ss, string->capacity);

    bool locked = false;
    for (int i = 0; i < string->length; i++) {
        if (i == begin) {
            locked = true;
            continue;
        } else if (i == end) {
            locked = false;
            continue;
        }

        if (!locked)
            CST_CatChar(&ss, CST_At(*string, i));
    }

    CST_Destroy(string);
    *string = ss;
}

CST_String CST_Subs(CST_String string, size_t begin, size_t end) {
    if (begin > end) {
        int temp = begin;
        begin = end;
        end = temp;
    }

    CST_String ss = CST_Create();
    for (int i = begin; i <= end; i++) {
        CST_CatChar(&ss, CST_At(string, i));
    }

    return ss;
}

CST_String CST_Ask(const char *msg) {
    CST_String string = CST_Create();
    _cst_enlarge_cond(&string, 128);

    printf("%s", msg);
    scanf("%s", string.data);
    string.length = CST_StrLen(string.data);
    string.capacity = 128;
    return string;
}

void CST_Clear(CST_String *string) {
    strcpy(string->data, "\0");
    string->length = 0;
}

void CST_Upper(CST_String *string) {
    if (!string || !string->data || string->length <= 0)
        return;

    for (int i = 0; i < string->length; i++) {
        if (string->data[i] >= 97 && string->data[i] <= 122)
            string->data[i] -= 32;
    }
}

void CST_Lower(CST_String *string) {
    if (!string || !string->data || string->length <= 0)
        return;
    
    for (int i = 0; i < string->length; i++) {
        if (string->data[i] >= 65 && string->data[i] <= 90)
            string->data[i] += 32;
    }
}

void CST_InverseCase(CST_String *string) {
    if (!string || !string->data || string->length <= 0)
        return;
    
    for (int i = 0; i < string->length; i++) {
        if (string->data[i] >= 65 && string->data[i] <= 90)
            string->data[i] += 32;
        else if (string->data[i] >= 97 && string->data[i] <= 122)
            string->data[i] -= 32;
    }
}