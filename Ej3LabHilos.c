#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE] = {0}; 


void* consumer(void *arg) {
    int processed = 0;
    while (processed < BUFFER_SIZE) {
        if (buffer[processed] != 0) {
            printf("Consumido: %d\n", buffer[processed]);
            buffer[processed] = 0; 
            processed++; 
        }
        
    }
    return NULL;
}

int main() {
    pthread_t thread; 

   
    pthread_create(&thread, NULL, consumer, NULL);

  
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("Ingrese un valor para la casilla %d: ", i + 1);
        scanf("%d", &buffer[i]); 
    }

   
    pthread_join(thread, NULL);
    printf("Hemos terminado.\n");

    return 0;
}
