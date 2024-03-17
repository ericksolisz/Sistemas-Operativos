#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_A, pid_B, pid_C, pid_D;
    int status;

    pid_A = fork();
    if (pid_A == 0) {
        printf("Soy A y mi PID es %d y el de mi padre es: %d\n", getpid(), getppid());
        wait(0);
        execl("/bin/rm", "rm", "-d", "new_folder", NULL);
    }
    waitpid(pid_A, &status, 0);
    if (WIFEXITED(status))
        printf("Soy M y mi pid es %d\n", getpid());

    pid_C = fork();
    if (pid_C == 0) {
        printf("Soy C y mi pid es %d y el de mi padre es %d\n", getpid(), getppid());
        execl("/bin/ls", "ls", NULL);
    }
    waitpid(pid_C, &status, 0);
    if (WIFEXITED(status))
        printf("Soy M y mi pid es %d\n", getpid());

    pid_D = fork();
    if (pid_D == 0) {
        printf("Soy D y mi PID es %d y el de mi padre es %d\n", getpid(), getppid());
        execl("/bin/ls", "ls", NULL);
    }

    pid_B = fork();
    if (pid_B == 0) {
        printf("Soy B y mi PID es %d y el de mi padre es %d\n", getpid(), getppid());
        execl("/bin/mkdir", "mkdir", "new_folder", NULL);
    }

    execl("/bin/ls", "ls", NULL);

    return 0;
}