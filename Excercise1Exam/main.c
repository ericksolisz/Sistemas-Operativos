#include <stdio.h>

int main() {
    int numLines, i, j;

    // asks for num lines
    printf("Ingrese el numero de lineas:\n ");
    scanf("%d", &numLines);

    // Print fugure
    for (i = 1; i <= numLines; i++) {
        for (j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
