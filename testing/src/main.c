#include <stdio.h>
#include <cstring/CString.h>

int main(void) {
    CST_String string = CST_From("Me gustan");
    CST_Cat(&string, " las patatas");

    printf("%s\n", CST_AsStr(string));

    CST_Destroy(&string);

    return 0;
}