#ifndef CString_H
#define CString_H

#define CST_BOOL bool
#define CST_TRUE 1
#define CST_FALSE 0

typedef struct cst_string {
    char *data;
    size_t length;
    size_t capacity;
} CST_String;

size_t CST_StrLen(const char *s);

CST_String CST_Create();
void CST_Destroy(CST_String *string);
CST_String CST_From(const char *content);
char *CST_AsStr(CST_String string);
size_t CST_Len(CST_String string);
void CST_Set(CST_String *string, char *content);
void CST_Cat(CST_String *string, char *content);
void CST_CatChar(CST_String *string, char c);

#endif // CString_H