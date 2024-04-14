#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int global_nums[3];
long factorial_results[3];

void* factorial(void *arg) {
    int index = *(int*)arg;
    int start = index > 0 ? global_nums[index - 1] + 1 : 1;
    int end = global_nums[index];
    long factorial = 1;
    for (int i = start; i <= end; i++) {
        factorial *= i;
    }
    factorial_results[index] = factorial;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int numbers[3] = {0, 1, 2};
    long input, result;

    printf("Ingrese un número divisible entre 3: ");
    scanf("%ld", &input);

    for (int i = 0; i < 3; i++) {
        global_nums[i] = (input / 3) * (i + 1);
    }

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, factorial, (void *)&numbers[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    result = factorial_results[0] * factorial_results[1] * factorial_results[2];
  printf("%ld * %ld * %ld ",factorial_results[0] , factorial_results[1] , factorial_results[2]);
    printf("El factorial de %ld es %ld\n", input, result);

    return 0;
}
