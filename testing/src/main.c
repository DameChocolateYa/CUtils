#include <stdio.h>
#include <cstring/CString.h>

int main(void) {
    CST_String string = CST_Ask(">> ");

    for (int i = 0; i < CST_Len(string); i++) {
        printf("%c\n", CST_At(string, i));
    }

    CST_Destroy(&string);
    return 0;
}