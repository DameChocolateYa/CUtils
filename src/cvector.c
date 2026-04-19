#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/cstring.h" // For String
#include "include/cvector.h"
#include <stdarg.h>

CVector cvector(size_t elem_size) {
    void *data = malloc(2 * elem_size); // capacity = 2 elements at init
    if (!data) {
        fprintf(stderr, "Could not allocate memory for CVector\n");
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
            fprintf(stderr, "cvector_push: Could not expand memory for push\n");
            return;
        }
    }

    memcpy((char *)vector->data + vector->size * vector->elem_size, elem, vector->elem_size);
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
        fprintf(stderr, "cvector_erase: index out of range\n");
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

void cvector_set(CVector *vector, size_t index, void *val) {
    if (!vector->data || !vector->is_membusy)
        return;
    
    if (index < 0 || index >= vector->size) {
        fprintf(stderr, "cvector_edit(generic): index out of range\n");
        return;
    }

    memcpy((char *)vector->data + index * vector->elem_size, val, vector->elem_size);
}

void cvector_pushi(CVector *vector, int val) {
    cvector_push(vector, &val);
}

void cvector_pushstr(CVector *vector, CString val) {
    cvector_push(vector, &val);
}

void cvector_pushf(CVector *vector, float val) {
    cvector_push(vector, &val);
}

void cvector_pushd(CVector *vector, double val) {
    cvector_push(vector, &val);
}

void cvector_pushvec(CVector *vector, CVector val) {
    cvector_push(vector, &val);
}

void cvector_pushm(CVector *vector, int n, ...) {
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        void *val = va_arg(args, void *);
        cvector_push(vector, val);
    }

    va_end(args);
}

void cvector_pushim(CVector *vector, int n, ...) {
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        int val = va_arg(args, int);
        cvector_pushi(vector, val);
    }

    va_end(args);
}

void cvector_pushstrm(CVector *vector, int n, ...) {
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        CString val = va_arg(args, CString);
        cvector_pushstr(vector, val);
    }

    va_end(args);
}

void cvector_pushfm(CVector *vector, int n, ...) {
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        float val = (float)va_arg(args, double);
        cvector_pushf(vector, val);
    }

    va_end(args);
}

void cvector_pushdm(CVector *vector, int n, ...) {
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        double val = va_arg(args, double);
        cvector_pushd(vector, val);
    }

    va_end(args);
}

void cvector_pushvecm(CVector *vector, int n, ...) {
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        CVector val = va_arg(args, CVector);
        cvector_pushvec(vector, val);
    }

    va_end(args);
}

void *cvector_get(CVector vector, size_t index) {
    if (!vector.data || !vector.is_membusy) {
        return NULL;
    }

    if (index < 0 || index >= vector.size) {
        fprintf(stderr, "cvector_get: index out of range\n");
        return NULL;
    }

    return (char *)vector.data + index * vector.elem_size;
}

int cvector_geti(CVector vector, size_t index) {
    int *ptr = (int *)cvector_get(vector, index);
    return ptr ? *ptr : 0;
}

CString cvector_getstr(CVector vector, size_t index) {
    CString *ptr = (CString *)cvector_get(vector, index);
    return ptr ? *ptr : (CString){NULL, 0};
}

float cvector_getf(CVector vector, size_t index) {
    float *ptr = (float *)cvector_get(vector, index);
    return ptr ? *ptr : .0;
}

double cvector_getd(CVector vector, size_t index) {
    double *ptr = (double *)cvector_get(vector, index);
    return ptr ? *ptr : .0;
}

CVector cvector_getvec(CVector vector, size_t index) {
    CVector *ptr = (CVector *)cvector_get(vector, index);
    return ptr ? *ptr : (CVector){NULL, 0, 0, 0, false};
}

void cvector_seti(CVector *vector, size_t index, int val) {
    cvector_set(vector, index, &val);
}

void cvector_setstr(CVector *vector, size_t index, CString val) {
    cvector_set(vector, index, &val);
}

void cvector_setf(CVector *vector, size_t index, float val) {
    cvector_set(vector, index, &val);
}

void cvector_setd(CVector *vector, size_t index, double val) {
    cvector_set(vector, index, &val);
}

void cvector_setvec(CVector *vector, size_t index, CVector val) {
    cvector_set(vector, index, &val);
}

void cvector_setim(CVector *vector, int n, ...) {
    if (!vector->data || !vector->is_membusy)
        return;

    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        int index = va_arg(args, int);
        int val = va_arg(args, int);

        if (index < 0 || index >= vector->size) {
            fprintf(stderr, "cvector_setim: index out of range - omiting current element\n");
            continue;
        }

        cvector_seti(vector, index, val);
    }

    va_end(args);
}

void cvector_setstrm(CVector *vector, int n, ...) {
    if (!vector->data || !vector->is_membusy)
        return;

    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        int index = va_arg(args, int);
        CString val = va_arg(args, CString);

        if (index < 0 || index >= vector->size) {
            fprintf(stderr, "cvector_setstrm: index out of range - omiting current element\n");
            continue;
        }

        cvector_setstr(vector, index, val);
    }

    va_end(args);
}

void cvector_setfm(CVector *vector, int n, ...) {
    if (!vector->data || !vector->is_membusy)
        return;

    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        int index = va_arg(args, int);
        float val = (float)va_arg(args, double);

        if (index < 0 || index >= vector->size) {
            fprintf(stderr, "cvector_setfm: index out of range - omiting current element\n");
            continue;
        }
        
        cvector_setf(vector, index, val);
    }

    va_end(args);
}

void cvector_setdm(CVector *vector, int n, ...) {
    if (!vector->data || !vector->is_membusy)
        return;

    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        int index = va_arg(args, int);
        double val = va_arg(args, double);

        if (index < 0 || index >= vector->size) {
            fprintf(stderr, "cvector_setdm: index out of range - omiting current element\n");
            continue;
        }

        cvector_setd(vector, index, val);
    }

    va_end(args);
}

void cvector_setvecm(CVector *vector, int n, ...) {
    if (!vector->data || !vector->is_membusy)
        return;

    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        int index = va_arg(args, int);
        CVector val = va_arg(args, CVector);

        if (index < 0 || index >= vector->size) {
            fprintf(stderr, "cvector_setvecm: index out of range - omiting current element\n");
            continue;
        }

        cvector_setvec(vector, index, val);
    }

    va_end(args);
}

void cvector_destroy(CVector *vector) {
    if (!vector->data || !vector->is_membusy)
        return;
    
    free(vector->data);
    vector->capacity = 0;
    vector->size = 0;
    vector->elem_size = 0;
    vector->is_membusy = false;
}

void cvector_destroym(int n, ...) {
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        CVector *vector = va_arg(args, CVector *);
        cvector_destroy(vector);
    }
}

// Due to cvector_destroy deletes all data
// Including outside of the struct (beacause data contains memory references)
// It is possible that the programmer desires to disable it and manage by himself the memory

void cvector_disable(CVector *vec) {
    vec->is_membusy = false;
}

// Just in case that the programmer regret about using the previous function ??
void cvector_enable(CVector *vec) {
    if (!vec->data) return; // It makes no sense to activate membusy flag if there is not data

    vec->is_membusy = true;
}

void cvector_cpy(CVector *dest, CVector src) {
    if (src.data || !src.is_membusy || src.size <= 0 || src.elem_size <= 0 || src.capacity == 0)
        return;
    
    dest->data = malloc(src.size + 1);
    if (!dest->data) {
        fprintf(stderr, "cvector_cpy: error allocating memory\n");
        return;
    }
    strcpy(dest->data, src.data);
    
    dest->size = src.size;
    dest->capacity = src.capacity;
    dest->elem_size = dest->elem_size;
    dest->is_membusy = true;
}

void cvector_cpy_and_push(CVector *dest, CVector src, size_t index) {
    if (dest->elem_size != src.elem_size) {
        fprintf(stderr, "cvector_cpy_in: vectors elem size are not equal\n");;
    }

    if (!src.data || !dest->data || !src.is_membusy || !dest->is_membusy)
        return;
    
    if (index < 0 || index >= src.size) {
        fprintf(stderr, "cvector_cpy_and_push: index out of range\n");
        return;
    }

    void *elem = cvector_get(src, index);
    cvector_push(dest, elem);
}

void cvector_cpy_and_pushm(CVector *dest, CVector src, int n, ...) {
    if (dest->elem_size != src.elem_size) {
        fprintf(stderr, "cvector_cpy_in: vectors elem size are not equal\n");;
    }

    if (!src.data || !dest->data || !src.is_membusy || !dest->is_membusy)
        return;
    
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        int index = va_arg(args, int);

        if (index < 0 || index >= src.size) {
            fprintf(stderr, "cvector_cpy_and_pushm: index out of range - omiting current element\n");
            continue;
        }

        void *elem = cvector_get(src, index);
        cvector_push(dest, elem);
    }

    va_end(args);
}

void cvector_cpy_in(CVector *dest, size_t to, CVector src, size_t from) {
    if (dest->elem_size != src.elem_size) {
        fprintf(stderr, "cvector_cpy_in: vectors elem size are not equal\n");;
    }

    if (!src.data || !dest->data || !src.is_membusy || !dest->is_membusy)
        return;
    
    if (from < 0 || from >= src.size || to < 0) {
        fprintf(stderr, "cvector_cpy_in: index out of range\n");
        return;
    }

    void *elem = cvector_get(src, from);

    if (to >= dest->size) {
        cvector_push(dest, elem);
        return;
    }

    memcpy(dest->data + to * dest->elem_size, elem, dest->elem_size);
}

void cvector_cpy_xelem_in(CVector *dest, CVector src, int n_par, ...) {
    if (dest->elem_size != src.elem_size) {
        fprintf(stderr, "cvector_cpy_in: vectors elem size are not equal\n");;
    }

    if (!src.data || !dest->data || !src.is_membusy || !dest->is_membusy)
        return;
    
    va_list args;
    va_start(args, n_par);
    
    for (int i = 0; i < n_par; i++) {
        int from = va_arg(args, int);
        int to = va_arg(args, int);

        if (from < 0 || from >= src.size || to < 0) {
            fprintf(stderr, "cvector_cpy_in: index out of range\n");
            return;
        }

        void *elem = cvector_get(src, from);

        if (to >= dest->size) {
            cvector_push(dest, elem);
            return;
        }

        memcpy(dest->data + to * dest->elem_size, elem, dest->elem_size);
    }
}

CVector cvector_clone(CVector og) {
    CVector newv = (CVector){NULL, 0, 0, 0, false};
    cvector_cpy(&newv, og);

    if (newv.data || !newv.is_membusy || newv.size <= 0 || newv.elem_size <= 0 || newv.capacity == 0)
        return (CVector){NULL, 0, 0, 0, false};

    return newv;
}

size_t cvector_ss() {
    return sizeof(CVector);
}