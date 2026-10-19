#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdio.h>
#include "CString.h"

#define CVT_BOOL bool
#define CVT_TRUE 1
#define CVT_FALSE 0

typedef struct cvt_vector {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} CVT_Vector;

struct cvt_vector _cvt_create(size_t size);

#define CVT_Create(T, ...) _cvt_create(sizeof(T));
size_t CVT_Size(CVT_Vector vector);
void CVT_Push(CVT_Vector *vector, const void *element);
void CVT_PushI32(CVT_Vector *vector, int element);
void CVT_PushFloat(CVT_Vector *vector, float element);
void CVT_PushDouble(CVT_Vector *vector, double element);
void CVT_PushBool(CVT_Vector *vector, bool element);
void CVT_PushChar(CVT_Vector *vector, char element);
void CVT_PushChars(CVT_Vector *vector, char *element);
void CVT_PushString(CVT_Vector *vector, CST_String element);
void *CVT_At(CVT_Vector vector, size_t index);
int CVT_AtI32(CVT_Vector vector, size_t index);
float CVT_AtFloat(CVT_Vector vector, size_t index);
double CVT_AtDouble(CVT_Vector vector, size_t index);
bool CVT_AtBool(CVT_Vector vector, size_t index);
char CVT_AtChar(CVT_Vector vector, size_t index);
char *CVT_AtChars(CVT_Vector vector, size_t index);
CST_String CVT_AtString(CVT_Vector vector, size_t index);
void CVT_Destroy(CVT_Vector *vector);
CVT_Vector CVT_Clone(CVT_Vector vector);
void CVT_Clear(CVT_Vector *vector);
size_t CVT_DataSize(CVT_Vector vector);
size_t CVT_Capacity(CVT_Vector vector);
void CVT_Realloc(CVT_Vector *vector, size_t capacity);

#endif //CVECTOR_H