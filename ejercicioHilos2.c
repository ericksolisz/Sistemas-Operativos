#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int counter;

void handle_alarm(int sig) {
    printf("Te tardaste mucho terminando el proceso\n");
    exit(0); 
}

void* increase_counter( void *args )
{
    while(1)
    {
        counter++;
        if (counter == 3) {
          
            signal(SIGALRM, handle_alarm);
            alarm(2); // essperar 2 
            pause(); 
        }
        sleep(1);
    }
    pthread_exit( NULL );
}

int main()
{
    pthread_t thread_1; 
    counter = 0;    
    
    pthread_create( &thread_1, NULL, &increase_counter, NULL );

    printf("Contando. Presiona cualquier tecla para ver la cuenta.\n");
    getchar();
    printf("El contador llegó a: %d.\n", counter);
    
    exit(0);
}