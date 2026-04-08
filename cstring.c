#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *data; // main string with memory allocation
    int size; // NEVER includes null terminator
    bool mem_busy; // == !data
} String;

String new_string() {
    String string;
    string.data = malloc(1);
    string.size = 0;
    
    if (!string.data) {
        perror("Could not create String\n");
        return (String) {NULL, 0};
    }
    
    string.mem_busy = true;
    
    return string;
}

String from_str(const char *src) {
    String string = new_string();
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

void set_str(String *string, const char *src) {
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

String clone_string(String string) {
    if (!string.data || !string.mem_busy) {
        perror("Could not clone string\n");
        return (String){NULL, 0};
    }
    
    String cloned = new_string(string.data);
    return cloned;
}

void clear_string(String *string) {
    if (!string->data || !string->mem_busy)
        return;
    
    strcpy(string->data, "");
    string->size = 0;
}

void cat_str(String *string, char *s2) {
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

void delete_string(String *string) {
    if (string->mem_busy) {
        free(string->data);
        string->size = 0;
    }
}

char *str(String string) {
    if (!string.data || !string.mem_busy) {
        return "(null)";
    }
    
    return string.data;
}
