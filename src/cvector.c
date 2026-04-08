#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t elem_size;
    bool is_membusy;
} CVector;

CVector cvector_new(size_t elem_size) {
    void *data = malloc(2 * elem_size); // 2 elements at init
    if (!data) {
        perror("Could not allocate memory for CVector\n");
        return (CVector){NULL, 0, 0, 0, false};
    }

    return (CVector){data, 0, 2, elem_size, true};
}

// Implement later...