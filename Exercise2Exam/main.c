#include <stdio.h>

// Calculate factorial
unsigned long long factorial(int num) {
    if (num == 0 || num == 1) {
        return 1;
    } else {
        return num * factorial(num - 1);
    }
}

int main() {
    int n, i;
    double result = 0.0;

    // input for n
    printf("Enter a value for n: ");
    scanf("%d", &n);

    // Calculate the result using the summation of factorials
    for (i = 1; i <= n - 1; i++) {
        result += factorial(i);
    }

    result /= factorial(n);

    printf("Result: %lf\n", result);

    return 0;
}
