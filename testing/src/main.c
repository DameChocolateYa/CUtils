#include <stdio.h>
#include <cstring/CString.h>
#include <string.h>

int main(void) {
    CST_String string = CST_From("abc");
    CST_String string2 = CST_Clone(string);

    CST_Set(&string2, "cba");

    printf("%s\n", CST_AsStr(string));

    CST_Destroy(&string);
    CST_Destroy(&string2);

    return 0;
}