#include <stdio.h>
#include <cutils/CVector.h>
#include <cutils/CString.h>

typedef struct color {
    int r;
    int g;
    int b;
} Color;

int main(void) {
    CVT_Vector vec = CVT_Create(Color);

    Color c1 = {255, 0, 255};
    CVT_Push(&vec, &c1);

    Color c2 = {0, 0, 255};
    CVT_Push(&vec, &c2);

    for (int i = 0; i < CVT_Size(vec); i++) {
        Color *c = CVT_At(vec, i);
        printf("%d, %d, %d\n", c->r, c->g, c->b);
    }

    CVT_Destroy(&vec);

    return 0;
}