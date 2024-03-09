#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int generateRandomNumber() {
    // Genera un número aleatorio entre 1 y 100
    return rand() % 100 + 1;
}

int main() {
    pid_t childQ, childA, childB, childM;
    int status, exitCode, successfulChildren = 0;

    // Proceso Q
    if ((childQ = fork()) == 0) {
        // Código del proceso Q
        printf("(Q) ID del proceso: %d\n", getpid());

        // Crear proceso A
        if ((childA = fork()) == 0) {
            // Código del proceso A
            srand(getpid()); // Establecer una semilla única para el proceso A
            printf("(A) ID del proceso: %d, Número aleatorio: %d\n", getpid(), generateRandomNumber());
            exit(0);
        } else if (childA > 0) {
            // Crear proceso B
            if ((childB = fork()) == 0) {
                // Código del proceso B
                srand(getpid()); // Establecer una semilla única para el proceso B
                printf("(B) ID del proceso: %d, Número aleatorio: %d\n", getpid(), generateRandomNumber());
                exit(0);
            } else if (childB > 0) {
                // Crear proceso M
                if ((childM = fork()) == 0) {
                    // Código del proceso M
                    srand(getpid()); // Establecer una semilla única para el proceso M
                    printf("(M) ID del proceso: %d, Número aleatorio: %d\n", getpid(), generateRandomNumber());
                    exit(0);
                } else if (childM > 0) {
                    // Esperar a que todos los hijos terminen
                    waitpid(childA, &status, 0);
                    exitCode = WEXITSTATUS(status);
                    if (exitCode == 0) {
                        successfulChildren++;
                    }

                    waitpid(childB, &status, 0);
                    exitCode = WEXITSTATUS(status);
                    if (exitCode == 0) {
                        successfulChildren++;
                    }

                    waitpid(childM, &status, 0);
                    exitCode = WEXITSTATUS(status);
                    if (exitCode == 0) {
                        successfulChildren++;
                    }

                    // Imprimir la cantidad de procesos hijos que terminaron correctamente
                    printf("(Q) Cantidad de procesos hijos que terminaron correctamente: %d\n", successfulChildren);
                }
            }
        }
    } else if (childQ > 0) {
        // Esperar a que el proceso Q termine
        waitpid(childQ, &status, 0);
    }

    return 0;
}
