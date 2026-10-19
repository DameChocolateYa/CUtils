#include "../include/CVector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void _cvt_enlarge(struct cvt_vector *_vector) {
    _vector->data = realloc(_vector->data, _vector->capacity * 2);
    _vector->capacity *= 2;

    if (!_vector->data)
        fprintf(stderr, "_cvt_enlarge: error adding more memory for the vector\n");
}

static void _cvt_enlarge_cond(struct cvt_vector *_vector, size_t min_size) {
    while (_vector->capacity <= min_size) {
        _cvt_enlarge(_vector);
    }
}

struct cvt_vector _cvt_create(size_t size) {
    struct cvt_vector _vector;

    _vector.data = malloc(size * 2);
    if (!_vector.data) {
        fprintf(stderr, "CVT_Create: error creating vector data\n");
        return (struct cvt_vector){0};
    }
    _vector.capacity = 2;
    _vector.size = 0;
    _vector.element_size = size;

    return _vector;
}

size_t CVT_Size(CVT_Vector vector) {
    return vector.size;
}

void CVT_Push(CVT_Vector *vector, const void *element) {
    if (!vector || !vector->data) {
        fprintf(stderr, "CST_Push: invalid vector\n");
        return;
    }

    _cvt_enlarge_cond(vector, vector->size + 1);

    memcpy((unsigned char *)vector->data + vector->size * vector->element_size, element, vector->element_size);
    vector->size++;
}

void CVT_PushI32(CVT_Vector *vector, int element) {
    if (vector->element_size != sizeof(int)) {
        fprintf(stderr, "CVT_PushI32: vector type is not i32\n");
        return;
    }

    CVT_Push(vector, &element);
}

void CVT_PushFloat(CVT_Vector *vector, float element) {
    if (vector->element_size != sizeof(float)) {
        fprintf(stderr, "CVT_PushFloat: vector type is not float\n");
        return;
    }

    CVT_Push(vector, &element);
}

void CVT_PushDouble(CVT_Vector *vector, double element) {
    if (vector->element_size != sizeof(double)) {
        fprintf(stderr, "CVT_PushDouble: vector type is not double\n");
        return;
    }

    CVT_Push(vector, &element);
}

void CVT_PushBool(CVT_Vector *vector, bool element) {
    if (vector->element_size != sizeof(bool)) {
        fprintf(stderr, "CVT_PushBool: vector type is not a bool\n");
        return;
    }

    CVT_Push(vector, &element);
}

void CVT_PushChar(CVT_Vector *vector, char element) {
    if (vector->element_size != sizeof(char)) {
        fprintf(stderr, "CVT_PushChar: vector type is not a char\n");
        return;
    }

    CVT_Push(vector, &element);
}

void CVT_PushChars(CVT_Vector *vector, char *element) {
    if (vector->element_size != sizeof(char *)) {
        fprintf(stderr, "CVT_PushChars: vector type is not char *\n");
        return;
    }

    CVT_Push(vector, element);
}

void CVT_PushString(CVT_Vector *vector, CST_String element) {
    if (vector->element_size != sizeof(CST_String)) {
        fprintf(stderr, "CVT_PushString: vector type is not CST_String\n");
        return;
    }

    CST_String clone = CST_Clone(element);

    CVT_Push(vector, &clone);
}

void *CVT_At(CVT_Vector vector, size_t index) {
    if (!vector.data) {
        fprintf(stderr, "CVT_At: invalid vector\n");
        return NULL;
    }

    if (index >= vector.size) {
        fprintf(stderr, "CVT_At: index out of range\n");
        return NULL;
    }

    return (unsigned char *)vector.data + index * vector.element_size;
}

int CVT_AtI32(CVT_Vector vector, size_t index) {
    if (vector.element_size != sizeof(int)) {
        fprintf(stderr, "CVT_AtI32: vector type is not i32\n");
        return 0;
    }

    int *element = (int *)CVT_At(vector, index);
    return *element;
}

float CVT_AtFloat(CVT_Vector vector, size_t index) {
    if (vector.element_size != sizeof(float)) {
        fprintf(stderr, "CVT_AtFloat: vector type is not float\n");
        return 0.0f;
    }

    float *element = (float *)CVT_At(vector, index);
    return *element;
}

double CVT_AtDouble(CVT_Vector vector, size_t index) {
    if (vector.element_size != sizeof(double)) {
        fprintf(stderr, "CVT_AtDouble: vector type is not double\n");
        return 0.0;
    }

    double *element = (double *)CVT_At(vector, index);
    return *element;
}

bool CVT_AtBool(CVT_Vector vector, size_t index) {
    if (vector.element_size != sizeof(bool)) {
        fprintf(stderr, "CVT_AtBool: vector type is not bool\n");
        return false;
    }

    bool *element = (bool *)CVT_At(vector, index);
    return *element;
}

char CVT_AtChar(CVT_Vector vector, size_t index) {
    if (vector.element_size != sizeof(char)) {
        fprintf(stderr, "CVT_AtChar: vector type is not char\n");
        return '\0';
    }

    char *element = (char *)CVT_At(vector, index);
    return *element;
}

char *CVT_AtChars(CVT_Vector vector, size_t index) {
    if (vector.element_size != sizeof(char *)) {
        fprintf(stderr, "CVT_AtChars: vector type is not char *\n");
        return NULL;
    }

    char *element = (char *)CVT_At(vector, index);
    return element;
}

CST_String CVT_AtString(CVT_Vector vector, size_t index) {
    if (vector.element_size != sizeof(CST_String)) {
        fprintf(stderr, "CVT_AtString: vector type is not a CST_String\n");
        return (struct cst_string){0};
    }

    CST_String *element = (CST_String *)CVT_At(vector, index);
    return *element;
}

void CVT_Destroy(CVT_Vector *vector) {
    if (!vector || !vector->data)
        return;
    
    free(vector->data);
    vector = NULL;
}

CVT_Vector CVT_Clone(CVT_Vector vector) {
    if (!vector.data) {
        fprintf(stderr, "CVT_Clone: invalid og vector\n");
        return (struct cvt_vector){0};
    }

    CVT_Vector clone = _cvt_create(vector.element_size);
    if (!clone.data)
        return (struct cvt_vector){0};
    
    _cvt_enlarge_cond(&clone, vector.size);

    memcpy(clone.data, vector.data, vector.size * vector.element_size);
    clone.size = vector.size;

    return clone;
}

void CVT_Clear(CVT_Vector *vector) {
    if (!vector || !vector->data)
        return;
    
    memset(vector->data, 0, vector->capacity * vector->element_size);
    vector->size = 0;
}

size_t CVT_DataSize(CVT_Vector vector) {
    return vector.element_size;
}

size_t CVT_Capacity(CVT_Vector vector) {
    return vector.capacity;
}

void CVT_Realloc(CVT_Vector *vector, size_t capacity) {
    if (!vector || !vector->data) {
        fprintf(stderr, "CVT_Realloc: invalid vector or data\n");
        return;
    }

    vector->data = realloc(vector->data, capacity * vector->element_size);
    if (!vector->data) {
        fprintf(stderr, "CVT_Realloc: error trying to realloc vector data\n");
        return;
    }

    vector->capacity = capacity;
}