#ifndef CString_H
#define CString_H

#define CST_BOOL bool
#define CST_TRUE 1
#define CST_FALSE 0

typedef struct cst_string {
    char *data;
    size_t length;
    size_t capacity;
    CST_BOOL enabled;
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
char CST_At(CST_String string, size_t index);
void CST_Cut(CST_String *string, size_t begin, size_t end);
CST_String CST_Subs(CST_String string, size_t begin, size_t end);
CST_String CST_Ask(const char *msg);
void CST_Clear(CST_String *string);
void CST_Upper(CST_String *string);
void CST_Lower(CST_String *string);
void CST_InverseCase(CST_String *string);
void CST_Resize(CST_String *string, size_t capacity);
void CST_Enable(CST_String *string);
void CST_Disable(CST_String *string);
void CST_ToggleAvailableState(CST_String *string);
void CST_SetAvailableState(CST_String *string, CST_BOOL status);

#endif // CString_H