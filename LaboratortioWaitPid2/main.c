#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t childB, childC, childE;

    // Proceso B
    if ((childB = fork()) == 0) {

        sleep(3);
        printf("B ha terminado. Retorno: 1\n");
        return 1;
    }

    // Proceso C
    if ((childC = fork()) == 0) {

        sleep(1);
        printf("C ha terminado. Retorno: 2\n");
        return 2;
    }

    // Proceso padre A
    int status;

    // Esperar a que termine B
    waitpid(childB, &status, 0);
    printf("Valor de retorno de B: %d\n", WEXITSTATUS(status));

    // Esperar a que termine C
    waitpid(childC, &status, 0);
    printf("Valor de retorno de C: %d\n", WEXITSTATUS(status));

    // Proceso E
    if ((childE = fork()) == 0) {
        // Código del proceso E
        printf("E ha terminado. Retorno: 3\n");
        return 3;
    }

    // Esperar a que termine E e imprimir su valor de retorno
    waitpid(childE, &status, 0);
    printf("Valor de retorno de E: %d\n", WEXITSTATUS(status));

    return 0;
}
