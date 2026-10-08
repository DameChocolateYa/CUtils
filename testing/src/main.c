#include <stdio.h>
#include <cstring/CString.h>

int main(void) {
    CST_String string = CST_Create();

    CST_CatChar(&string, 'h');
    CST_CatChar(&string, 'o');
    CST_CatChar(&string, 'l');
    CST_CatChar(&string, 'l');
    CST_CatChar(&string, 'i');

    printf("%c\n", CST_At(string, 1));

    CST_Destroy(&string);
    return 0;
}