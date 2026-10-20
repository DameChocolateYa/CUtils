#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/CString.h"

static void _cst_enlarge(struct cst_string *string) {
    if (string->enabled == CST_FALSE)
        return;

    string->data = realloc(string->data, string->capacity * 2);
    if (!string->data) {
        fprintf(stderr, "_cst_enlarge: could not reallocate memory for string enlargment\n");
        return;
    }
    string->capacity *= 2;
}

static void _cst_enlarge_cond(struct cst_string *string, size_t min) {
    if (string->enabled == CST_FALSE)
        return;

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
    string.enabled = CST_TRUE;

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
    if (!string->data || string->enabled == CST_FALSE)
        return;
    
    free(string->data);
    string = NULL;
}

CST_String CST_From(const char *content) {
    CST_String string;
    string.enabled = CST_TRUE;

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
    if (string.enabled == CST_FALSE)
        return "(null)";

    if (!string.data)
        return "(null)";
    
    return string.data;
}

size_t CST_Len(CST_String string) {
    if (string.enabled == CST_FALSE)
        return 0;

    return string.length;
}

void CST_Set(CST_String *string, char *content) {
    if (string->enabled == CST_FALSE)
        return;

    _cst_enlarge_cond(string, CST_StrLen(content) + 1);
    strcpy(string->data, content);
    string->length = CST_StrLen(content);
}

void CST_Cat(CST_String *string, char *content) {
    if (string->enabled == CST_FALSE)
        return;

    _cst_enlarge_cond(string, string->length + CST_StrLen(content) + 1);
    strcat(string->data, content);
    string->length += CST_StrLen(content);
}

void CST_CatChar(CST_String *string, char c) {
    if (string->enabled == CST_FALSE)
        return;

    _cst_enlarge_cond(string, string->length + 2);
    string->data[string->length] = c;
    string->data[string->length + 1] = '\0';
    string->length++;
}

char CST_At(CST_String string, size_t index) {
    if (string.enabled == CST_FALSE)
        return '\0';

    if (index < 0 || index > string.length) {
        fprintf(stderr, "CST_At: index out of range\n");
        return '\0';
    }

    return string.data[index];
}

void CST_Cut(CST_String *string, size_t begin, size_t end) {
    if (string->enabled == CST_FALSE)
        return;

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
    if (string.enabled == CST_FALSE)
        return string;

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
    string.enabled = CST_TRUE;
    _cst_enlarge_cond(&string, 128);

    printf("%s", msg);
    scanf("%s", string.data);
    string.length = CST_StrLen(string.data);
    string.capacity = 128;
    return string;
}

void CST_Clear(CST_String *string) {
    if (string->enabled == CST_FALSE)
        return;

    strcpy(string->data, "\0");
    string->length = 0;
}

void CST_Upper(CST_String *string) {
    if (!string || !string->data || string->length <= 0 || string->enabled == CST_FALSE)
        return;

    for (int i = 0; i < string->length; i++) {
        if (string->data[i] >= 97 && string->data[i] <= 122)
            string->data[i] -= 32;
    }
}

void CST_Lower(CST_String *string) {
    if (!string || !string->data || string->length <= 0 || string->enabled == CST_FALSE)
        return;
    
    for (int i = 0; i < string->length; i++) {
        if (string->data[i] >= 65 && string->data[i] <= 90)
            string->data[i] += 32;
    }
}

void CST_InverseCase(CST_String *string) {
    if (!string || !string->data || string->length <= 0 || string->enabled == CST_FALSE)
        return;
    
    for (int i = 0; i < string->length; i++) {
        if (string->data[i] >= 65 && string->data[i] <= 90)
            string->data[i] += 32;
        else if (string->data[i] >= 97 && string->data[i] <= 122)
            string->data[i] -= 32;
    }
}

void CST_Resize(CST_String *string, size_t capacity) {
    if (!string || !string->data || string->enabled == CST_FALSE)
        return;
    
    string->data = realloc(string->data, capacity);
    if (!string->data)
        fprintf(stderr, "CST_Resize: error trying to realloc String memory\n");
}

void CST_Enable(CST_String *string) {
    string->enabled = CST_TRUE;
}

void CST_Disable(CST_String *string) {
    string->enabled = CST_FALSE;
}

void CST_ToggleAvailableState(CST_String *string) {
    string->enabled = string->enabled == CST_TRUE ? CST_FALSE : CST_TRUE;
}

void CST_SetAvailableState(CST_String *string, CST_BOOL status) {
    string->enabled = status;
}

CST_String CST_Clone(CST_String string) {
    CST_String ss;
    ss.data = malloc(string.capacity);

    if (!ss.data) {
        fprintf(stderr, "CST_Clone: error cloning string\n");
        return ss;
    }

    strcpy(ss.data, string.data);
    ss.length = string.length;
    ss.enabled = string.enabled;
    ss.capacity = string.capacity;

    return ss;
}
CVT_Vector CST_Chars(CST_String string) {
    CVT_Vector chars = CVT_Create(char);

    for (int i = 0; i < string.length; i++) {
        CVT_PushChar(&chars, string.data[i]);
    }

    return chars;
}