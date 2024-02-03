#include <stdio.h>

int main() {

    int input;

    printf("Ingresa el numero\n" );
    scanf("%d",&input );
    int num=input+1;


    int result;
    int found=1;


    while (found!=2)
    {
        int factors = 0;
        for (int i=1; num >= i; i++) {
            ///residue of  number/i ==0
            if (num%i == 0) { factors++; }
        }
        if (factors == 2) { result = num; found=2;}

        num++;
    }


    printf("El numero primo mas proximo es:\n" );
    printf("%d",result );
}