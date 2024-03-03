#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

void checkError(int value) {
    if (value < 0) {
        if (errno == EAGAIN) {
            printf("Archivo bloqueado.\n");
        } else if (errno == EACCES) {
            printf("Problema de permisos del archivo.\n");
        } else if (errno == EBADF) {
            printf("Mal descriptor del archivo.\n");
        } else {
            printf("Error desconocido.\n");
        }

        exit(1);
    }
}

void writeFloatArrayToFile(const char *filename, float *array, size_t size) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    checkError(fd);

    write(fd, array, size);

    close(fd);
}

void readAndPrintFloatArray(const char *filename, size_t size) {
    float readArray[size];
    int fd = open(filename, O_RDONLY);
    checkError(fd);

    read(fd, readArray, sizeof(float) * size);

    printf("Contenido de %s:\n", filename);
    for (size_t i = 0; i < size; i++) {
        printf("%f\n", readArray[i]);
    }

    close(fd);
}

void writeFloatValuesOneByOne(const char *filename, float *values, size_t count) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    checkError(fd);

    for (size_t i = 0; i < count; i++) {
        int n = write(fd, &values[i], sizeof(float));
        printf("n for write %zu: %d\n", i + 1, n);

        checkError(n);
    }

    close(fd);
}

void readAndPrintFloatValues(const char *filename, size_t count) {
    float readValues[count];
    int fd = open(filename, O_RDONLY);
    checkError(fd);

    printf("Contenido de %s:\n", filename);
    for (size_t i = 0; i < count; i++) {
        read(fd, &readValues[i], sizeof(float));
        printf("%f\n", readValues[i]);
    }

    close(fd);
}

int main() {
    // Programa 1
    float array1[] = {1.23, 4.56, 7.89, 10.11, 12.13};
    writeFloatArrayToFile("datos.txt", array1, sizeof(array1));

    // Programa 2
    readAndPrintFloatArray("datos.txt", sizeof(array1) / sizeof(float));

    // Programa 3
    float values2[] = {2.34, 5.67, 8.90, 11.12, 13.14};
    writeFloatValuesOneByOne("datos2.txt", values2, sizeof(values2) / sizeof(float));

    // Programa 4
    readAndPrintFloatValues("datos2.txt", sizeof(values2) / sizeof(float));

    return 0;
}
