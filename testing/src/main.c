#include <cutils/CString.h>
#include <cutils/CVector.h>
#include <cutils/CMath.h>

int main(void) {
    CST_String string = CST_From("Hola");

    CVT_Vector v = CST_Chars(string);
    for (int i = 0; i < v.size; i++) {
        printf("%c\n", CVT_AtChar(v, i));
    }

    CVT_Destroy(&v);
    CST_Destroy(&string);

    return 0;
}