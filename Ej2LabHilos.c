#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int array[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int subarray1[4], subarray2[4], subarray3[4];
int found_flag = 0;
int target_number;

void* search_subarray(void *args) {
    int *subarray = (int *)args;
    for (int i = 0; i < 4; i++) {
        if (subarray[i] == target_number) {
            found_flag = 1;
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int i, rc;

    printf("Ingresa el numero a buscar: ");
    scanf("%d", &target_number);

    for (i = 0; i < 4; i++) {
        subarray1[i] = array[i];
        subarray2[i] = array[i + 4];
        subarray3[i] = array[i + 8];
    }

    pthread_create(&threads[0], NULL, search_subarray, (void *)subarray1);

    pthread_create(&threads[1], NULL, search_subarray, (void *)subarray2);

    pthread_create(&threads[2], NULL, search_subarray, (void *)subarray3);


    for (i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    if (found_flag == 1) {
        printf("El numero %d fue encontrado en el arreglo.\n", target_number);
    } else {
        printf("el numero %d no esta en el arreglo.\n", target_number);
    }

    return 0;
}