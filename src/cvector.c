#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/cstring.h" // For String
#include "include/cvector.h"

CVector cvector_new(size_t elem_size) {
    void *data = malloc(2 * elem_size); // 2 elements at init
    if (!data) {
        perror("Could not allocate memory for CVector\n");
        return (CVector){NULL, 0, 0, 0, false};
    }

    return (CVector){data, 0, 2, elem_size, true};
}

void cvector_push(CVector *vector, void *elem) {
    if (!vector->data || !vector->is_membusy || !elem) {
        return;
    }

    if (vector->size + 1 >= vector->capacity) {
        vector->capacity *= 2;
        vector->data = realloc(vector->data, vector->capacity * vector->elem_size);

        if (!vector->data) {
            perror("cvector_push: Could not expand memory for push\n");
            return;
        }
    }

    memcpy(vector->data + vector->size * vector->elem_size, elem, vector->elem_size);
    (vector->size)++;
}

void cvector_pop(CVector *vector) {
    if (!vector->data || !vector->is_membusy || vector->size <= 0)
        return;
    
    vector->size -= 1;
    memset((char *)vector->data + (vector->size) * vector->elem_size, 0xDD, vector->elem_size);
}

void cvector_eraseat(CVector *vector, size_t index) {
    if (!vector->data || !vector->is_membusy) {
        return;
    }

    if (index < 0 || index >= vector->size) {
        perror("cvector_erase: index out of range\n");
        return;
    }

    memmove((char *)vector->data + index * vector->elem_size,
        (char *)vector->data + (index + 1) * vector->elem_size,
        (vector->size - index -1) * vector->elem_size);
    
    vector->size--;
}

void cvector_eraseall(CVector *vector) {
    if (!vector->data || !vector->is_membusy) {
        return;
    }

    memset((char *)vector->data, 0xDD, (vector->size - 1) * vector->elem_size);
    vector->size = 0;
}

void cvector_pushint(CVector *vector, int val) {
    cvector_push(vector, &val);
}

void cvector_pushcstring(CVector *vector, CString val) {
    cvector_push(vector, &val);
}

void *cvector_get(CVector vector, size_t index) {
    if (!vector.data || !vector.is_membusy) {
        return NULL;
    }

    if (index < 0 || index >= vector.size) {
        perror("cvector_get: index out of range\n");
        return NULL;
    }

    return (char *)vector.data + index * vector.elem_size;
}

int cvector_getint(CVector vector, size_t index) {
    int *ptr = (int *)cvector_get(vector, index);
    return ptr ? *ptr : 0;
}

CString cvector_getcstring(CVector vector, size_t index) {
    CString *ptr = (CString *)cvector_get(vector, index);
    return ptr ? *ptr : (CString){NULL, 0};
}