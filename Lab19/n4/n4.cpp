#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void Load(int** incomes, int* count);
void SaveHighIncomes(int* incomes, int count);

void main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printf("Hello! It is Task for High Incomes!\n");

    int* incomes = NULL;
    int n = 0;

    Load(&incomes, &n);
    SaveHighIncomes(incomes, n);

    // Освобождение памяти
    if (incomes != NULL) {
        free(incomes);
    }
}

void Load(int** incomes, int* count) {
    FILE* fin = fopen("in4.txt", "rt");
    if (fin == NULL) {
        printf("Входной файл не найден\n");
        return;
    }

    if (fscanf(fin, "%d", count) != 1 || *count <= 0) {
        printf("Ошибка чтения количества доходов или оно некорректно\n");
        fclose(fin);
        return;
    }

    // Выделение памяти для массива доходов
    *incomes = (int*)malloc(*count * sizeof(int));
    if (*incomes == NULL) {
        printf("Ошибка выделения памяти для доходов\n");
        fclose(fin);
        return;
    }

    // Чтение доходов
    for (int i = 0; i < *count; i++) {
        if (fscanf(fin, "%d", &(*incomes)[i]) != 1) {
            printf("Ошибка чтения дохода %d\n", i + 1);
            free(*incomes);
            *incomes = NULL;
            *count = 0;
            fclose(fin);
            return;
        }
    }

    fclose(fin);
}

void SaveHighIncomes(int* incomes, int count) {
    if (incomes == NULL || count <= 0) {
        printf("Нет данных для обработки\n");
        return;
    }

    // Определение максимального дохода
    int maxIncome = incomes[0];
    for (int i = 1; i < count; i++) {
        if (incomes[i] > maxIncome) {
            maxIncome = incomes[i];
        }
    }
    printf("Максимальный доход: %d\n", maxIncome);

    // Порог для высоких доходов
    int threshold = (2 * maxIncome) / 3;
    printf("Порог для высоких доходов: %d\n", threshold);

    // Подсчёт доходов, подходящих под условие
    int highCount = 0;
    for (int i = 0; i < count; i++) {
        if (incomes[i] >= threshold) {
            highCount++;
        }
    }

    // Выделение памяти для высоких доходов
    int* highIncomes = (int*)malloc(highCount * sizeof(int));
    if (highIncomes == NULL) {
        printf("Ошибка выделения памяти для высоких доходов\n");
        return;
    }

    // Сохранение высоких доходов
    int index = 0;
    for (int i = 0; i < count; i++) {
        if (incomes[i] >= threshold) {
            highIncomes[index++] = incomes[i];
        }
    }

    // Сохранение результата в файл
    FILE* fout = fopen("out4.txt", "wt");
    if (fout == NULL) {
        printf("Не удалось создать выходной файл\n");
        free(highIncomes);
        return;
    }

    fprintf(fout, "%d\n", highCount);
    for (int i = 0; i < highCount; i++) {
        fprintf(fout, "%d ", highIncomes[i]);
    }

    fclose(fout);
    free(highIncomes);
    printf("Результат сохранён в файл out4.txt\n");
}
