#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t childL, childD;
    pid_t parent_pid = getpid();

    // Proceso L
    if ((childL = fork()) == 0) {
        // Código del proceso L
        sleep(3);
        printf("Termine mi ejecusion, PID: %d, PID del padre: %d\n", getpid(), getppid());
        return 0;
    }

    // Proceso D
    if ((childD = fork()) == 0) {
        // Código del proceso D
        sleep(1);
        printf("Termine mi ejecusion, PID: %d, PID del padre: %d\n", getpid(), getppid());
        return 0;
    }

    // Código del proceso padre
    while (1) {
        // Esperar a que algún hijo termine
        int status;
        pid_t terminated_child = wait(&status);
        if (terminated_child == childL || terminated_child == childD) {
            printf("Uno de mis hijos ha terminado su ejecucion.\n");
        }

        // Si ambos hijos han terminado, salir del bucle
        if (waitpid(childL, NULL, WNOHANG) > 0 && waitpid(childD, NULL, WNOHANG) > 0) {
            printf("Ambos hijos han terminado su ejecucion.\n");
            break;
        }
    }

    return 0;
}
