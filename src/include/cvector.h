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

extern CVector cvector(size_t elem_size);
extern void cvector_push(CVector *vector, void *elem);
extern void cvector_pop(CVector *vector);
extern void cvector_set(CVector *vector, size_t index, void *val);

extern void cvector_eraseat(CVector *vector, size_t index);
extern void cvector_eraseall(CVector *vector);

extern void cvector_pushi(CVector *vector, int val);
extern void cvector_pushstr(CVector *vector, CString val);
extern void cvector_pushf(CVector *vector, float val);
extern void cvector_pushd(CVector *vector, double val);
extern void cvector_pushvec(CVector *vector, CVector val);

extern void cvector_pushm(CVector *vector, int n, ...);
extern void cvector_pushim(CVector *vector, int n, ...);
extern void cvector_pushstrm(CVector *vector, int n, ...);
extern void cvector_pushfm(CVector *vector, int n, ...);
extern void cvector_pushdm(CVector *vector, int n, ...);
extern void cvector_pushvecm(CVector *vector, int n, ...);

extern void *cvector_get(CVector vector, size_t index);
extern int cvector_geti(CVector vector, size_t index);
extern CString cvector_getstr(CVector vector, size_t index);
extern float cvector_getf(CVector vector, size_t index);
extern double cvector_getd(CVector vector, size_t index);
extern CVector cvector_getvec(CVector vector, size_t index);

extern void cvector_seti(CVector *vector, size_t index, int val);
extern void cvector_setstr(CVector *vector, size_t index, CString val);
extern void cvector_setf(CVector *vector, size_t index, float val);
extern void cvector_setd(CVector *vector, size_t index, double val);
extern void cvector_setvec(CVector *vector, size_t index, CVector val);

extern void cvector_setim(CVector *vector, int n, ...);
extern void cvector_setstrm(CVector *vector, int n, ...);
extern void cvector_setfm(CVector *vector, int n, ...);
extern void cvector_setdm(CVector *vector, int n, ...);
extern void cvector_setvecm(CVector *vector, int n, ...);

extern void cvector_cpy_and_push(CVector *dest, CVector src, size_t index);
extern void cvector_cpy_and_pushm(CVector *dest, CVector src, int n, ...);
extern void cvector_cpy_in(CVector *dest, size_t to, CVector src, size_t from);
extern void cvector_cpy_xelem_in(CVector *dest, CVector src, int n_par, ...);

extern void cvector_cpy(CVector *dest, CVector src);
extern CVector cvector_clone(CVector og);

extern void cvector_destroy(CVector *vector);
extern void cvector_destroym(int n, ...);

extern void cvector_disable(CVector *vector);
extern void cvector_enable(CVector *vector);

extern size_t cvector_ss();

#endif