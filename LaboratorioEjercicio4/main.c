#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void printProcessInfo(char processLetter, char parentLetter) {
    printf("(%c) ID del proceso: %d, Padre: (%c) ID: %d\n", processLetter, getpid(), parentLetter, getppid());
}

int main() {
    pid_t childR, childT, childW, childV, childS, childL, childP;
    int status;

    // Proceso R
    if ((childR = fork()) == 0) {
        // Código del proceso R
        printProcessInfo('R', 'R');

        // Crear proceso T
        if ((childT = fork()) == 0) {
            // Código del proceso T
            printProcessInfo('T', 'R');

            // Crear proceso V
            if ((childV = fork()) == 0) {
                // Código del proceso V
                printProcessInfo('V', 'T');
            } else if (childV > 0) {
                // Esperar a que el proceso V termine
                waitpid(childV, &status, 0);
            }
        } else if (childT > 0) {
            // Crear proceso W
            if ((childW = fork()) == 0) {
                // Código del proceso W
                printProcessInfo('W', 'R');

                // Crear proceso S
                if ((childS = fork()) == 0) {
                    // Código del proceso S
                    printProcessInfo('S', 'W');
                } else if (childS > 0) {
                    // Esperar a que el proceso S termine
                    waitpid(childS, &status, 0);
                }

                // Crear proceso L
                if ((childL = fork()) == 0) {
                    // Código del proceso L
                    printProcessInfo('L', 'W');

                    // Crear proceso P
                    if ((childP = fork()) == 0) {
                        // Código del proceso P
                        printProcessInfo('P', 'L');
                    } else if (childP > 0) {
                        // Esperar a que el proceso P termine
                        waitpid(childP, &status, 0);
                    }
                } else if (childL > 0) {
                    // Esperar a que el proceso L termine
                    waitpid(childL, &status, 0);
                }
            } else if (childW > 0) {
                // Esperar a que el proceso W termine
                waitpid(childW, &status, 0);
            }
        }
    } else if (childR > 0) {
        // Esperar a que el proceso R termine
        waitpid(childR, &status, 0);
    }

    return 0;
}
