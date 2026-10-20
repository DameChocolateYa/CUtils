#ifndef CMATH_H
#define CMATH_H

typedef struct cmt_vec2 {
    int x;
    int y;
} CMT_Vec2;

typedef struct cmt_vec3 {
    int x;
    int y;
    int z;
} CMT_Vec3;

int CMT_SumI32(int count, ...);
int CMT_SubI32(int count, ...);
int CMT_MulI32(int count, ...);

#endif // CMATH_H