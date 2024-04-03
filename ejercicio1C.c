#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


void signal_handler_sigusr2(int signum) {
    for (int i = 0; i <= 10; i++) {
        printf("%d\n", i);
    }
}

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) {
        
        signal(SIGUSR2, signal_handler_sigusr2);
        printf("Proceso hijo en espera de señal SIGUSR2.\n");
        pause(); 
    } else if (pid > 0) {
        // padre
        sleep(1); 
        printf("Enviando señal SIGUSR2 al proceso hijo.\n");
        kill(pid, SIGUSR2); 
        wait(&status);
    }
    
    return 0;


}