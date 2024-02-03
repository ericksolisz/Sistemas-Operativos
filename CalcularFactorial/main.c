#include <stdio.h>

int Factorial(int num)
{
    int result=1;
    for (int i = 1; num >= i; i++)
    {
        result=result*i;
    }

    return result;
}

int main() {
    int num;
    int result;
    printf("Ingrese el numero que desea calcular: \n");
    scanf("%d", &num);

    printf("El resultado es: %d", Factorial(num));


}

