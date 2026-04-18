#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdbool.h>
#include <stdlib.h>

#include "cstring.h"

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t elem_size;
    bool is_membusy;
} CVector;

extern CVector cvector_new(size_t elem_size);
extern void cvector_push(CVector *vector, void *elem);
extern void cvector_pop(CVector *vector);

extern void cvector_eraseat(CVector *vector, size_t index);
extern void cvector_eraseall(CVector *vector);

extern void cvector_pushint(CVector *vector, int val);
extern void cvector_pushfloat(CVector *vector, float val);
extern void cvector_pushcstring(CVector *vector, CString val);
extern void cvector_pushvec(CVector *vector, CVector val);

extern void *cvector_get(CVector vector, size_t index);
extern int cvector_getint(CVector vector, size_t index);
extern CString cvector_getcstring(CVector vector, size_t index);
extern float cvector_getfloat(CVector vector, size_t index);
extern CVector cvector_getvec(CVector vector, size_t index);

extern void cvector_cpy(CVector *dest, CVector src);
extern CVector cvector_clone(CVector og);

extern void cvector_destroy(CVector *vector);

#endif