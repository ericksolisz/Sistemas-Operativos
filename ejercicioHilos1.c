#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS_NO 10


void* print_hello_world(void *args) {
    int index = args; 

    if (index % 2 == 0) {
        printf("Soy par.\n");
    } else {
        printf("Soy impar.\n");
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[THREADS_NO];
    int state, i;
  

    for (i = 0; i < THREADS_NO; i++) {
       
        pthread_create(&threads[i], NULL, print_hello_world, (void*)i);
       
        printf("Main creo un hilo en la iteración %d.\n", i);
    }

    
    for (i = 0; i < THREADS_NO; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0; 
}
