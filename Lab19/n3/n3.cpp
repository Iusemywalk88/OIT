#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void Load(float** temps, int* count);
void SaveResult(float* temps, int count);

void main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printf("Hello! It is Task for Temperatures!\n");

    float* temperatures = NULL;
    int n = 0;

    Load(&temperatures, &n);
    SaveResult(temperatures, n);

    // Освобождение памяти
    if (temperatures != NULL) {
        free(temperatures);
    }
}

void Load(float** temps, int* count) {
    FILE* fin = fopen("in3.txt", "rt");
    if (fin == NULL) {
        printf("Входной файл не найден\n");
        return;
    }

    if (fscanf(fin, "%d", count) != 1 || *count <= 0) {
        printf("Ошибка чтения количества температур или оно некорректно\n");
        fclose(fin);
        return;
    }

    // Выделение памяти для массива температур
    *temps = (float*)malloc(*count * sizeof(float));
    if (*temps == NULL) {
        printf("Ошибка выделения памяти для температур\n");
        fclose(fin);
        return;
    }

    // Чтение температур
    for (int i = 0; i < *count; i++) {
        if (fscanf(fin, "%f", &(*temps)[i]) != 1) {
            printf("Ошибка чтения температуры %d\n", i + 1);
            free(*temps);
            *temps = NULL;
            *count = 0;
            fclose(fin);
            return;
        }
    }

    fclose(fin);
}

void SaveResult(float* temps, int count) {
    if (temps == NULL || count <= 0) {
        printf("Нет данных для обработки\n");
        return;
    }

    // Вычисление среднего арифметического
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += temps[i];
    }
    float average = sum / count;
    printf("Среднее арифметическое: %.2f\n", average);

    // Подсчёт температур, подходящих под условие
    int validCount = 0;
    for (int i = 0; i < count; i++) {
        if (temps[i] > 0 && temps[i] < average) {
            validCount++;
        }
    }

    // Выделение памяти для подходящих температур
    float* validTemps = (float*)malloc(validCount * sizeof(float));
    if (validTemps == NULL) {
        printf("Ошибка выделения памяти для выходных данных\n");
        return;
    }

    // Сохранение подходящих температур
    int index = 0;
    for (int i = 0; i < count; i++) {
        if (temps[i] > 0 && temps[i] < average) {
            validTemps[index++] = temps[i];
        }
    }

    // Сохранение результата в файл
    FILE* fout = fopen("out3.txt", "wt");
    if (fout == NULL) {
        printf("Не удалось создать выходной файл\n");
        free(validTemps);
        return;
    }

    fprintf(fout, "%d\n", validCount);
    for (int i = 0; i < validCount; i++) {
        fprintf(fout, "%.2f ", validTemps[i]);
    }

    fclose(fout);
    free(validTemps);
    printf("Результат сохранён в файл out3.txt\n");
}
