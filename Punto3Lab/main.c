#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ARRAY_SIZE 10

void generateAndSaveArray(const char *filename, int start, int step) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    int array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = start + i * step;
        fprintf(file, "%d\n", array[i]);
    }

    fclose(file);
}

void printArray(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    int value;
    printf("Contenido del archivo %s: ", filename);
    while (fscanf(file, "%d", &value) != EOF) {
        printf("%d ", value);
    }
    printf("\n");

    fclose(file);
}


int main() {
    pid_t child1, child2;
    int status;

    // Crear el primer hijo
    if ((child1 = fork()) == 0) {
        // Código del primer hijo
        generateAndSaveArray("N.dat", 0, 2);
        exit(EXIT_SUCCESS);
    } else if (child1 < 0) {
        perror("Error al crear el primer hijo");
        exit(EXIT_FAILURE);
    }

    // Crear el segundo hijo
    if ((child2 = fork()) == 0) {
        // Código del segundo hijo
        generateAndSaveArray("M.dat", 1, 2);
        exit(EXIT_SUCCESS);
    } else if (child2 < 0) {
        perror("Error al crear el segundo hijo");
        exit(EXIT_FAILURE);
    }

    // Esperar a que ambos hijos terminen
    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);

    // Código del padre
    printf("Arreglo N:\n");
    printArray("N.dat");

    printf("\nArreglo M:\n");
    printArray("M.dat");

    FILE *fileN = fopen("N.dat", "r");
    FILE *fileM = fopen("M.dat", "r");

    if (fileN == NULL || fileM == NULL) {
        perror("Error al abrir los archivos");
        exit(EXIT_FAILURE);
    }

    int arrayN[ARRAY_SIZE], arrayM[ARRAY_SIZE];

    // Leer los datos de los archivos
    for (int i = 0; i < ARRAY_SIZE; i++) {
        fscanf(fileN, "%d", &arrayN[i]);
        fscanf(fileM, "%d", &arrayM[i]);
    }

    fclose(fileN);
    fclose(fileM);

    // Calcular la suma elemento por elemento e imprimir el resultado
    printf("\nSuma de los arreglos elemento por elemento:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int suma = arrayN[i] + arrayM[i];
        printf("%d + %d = %d\n", arrayN[i], arrayM[i], suma);
    }

    return 0;
}
