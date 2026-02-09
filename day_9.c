#include <stdio.h>
#include <string.h>

int main() {
    char str[1000];

    printf("Enter code name: ");
    scanf("%s", str);

    int len = strlen(str);

    printf("Mirror format: ");
    for(int i = len - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }

    return 0;
}
