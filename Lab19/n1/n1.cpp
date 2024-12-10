#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h> // Для работы с строками
int a[1000]; // массив. 1000 - максимально допустимое количество элементов
int n;       // Реальное количество элементов в массиве

void Load();
void SaveResult();

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printf("Hello! It is Task1!\n");

    Load();
    SaveResult();
}

void Load() {
    // Открытие входного файла
    FILE* fin = fopen("in1.txt", "rt");
    if (fin == NULL) {
        printf("Входной файл не найден\n");
        return;
    }

    // Загрузка массива из входного файла
    if (fscanf(fin, "%d", &n) != 1) {
        printf("Ошибка чтения количества элементов\n");
        fclose(fin);
        return;
    }
    printf("Количество элементов: %d\n", n);

    for (int i = 0; i < n; i++) {
        if (fscanf(fin, "%d", &a[i]) != 1) {
            printf("Ошибка чтения элемента %d\n", i + 1);
            fclose(fin);
            return;
        }
        printf("Прочитано число: %d\n", a[i]);
    }

    // Закрытие входного файла
    fclose(fin);
}


void SaveResult() {
    if (n <= 0) {
        printf("Ошибка: массив пуст или количество элементов равно 0\n");
        return;
    }

    float s = 0;
    for (int i = 0; i < n; i++) {
        s += a[i];
    }
    float sa = s / n;
    printf("Среднее арифметическое: %.2f\n", sa);

    int m = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > sa) {
            m++;
        }
    }
    printf("Количество элементов больше среднего: %d\n", m);

    FILE* fout = fopen("out1.txt", "wt");
    if (fout == NULL) {
        printf("Не удалось создать выходной файл\n");
        return;
    }

    fprintf(fout, "%d\n", m);
    for (int i = 0; i < n; i++) {
        if (a[i] > sa) {
            fprintf(fout, "%d ", a[i]);
        }
    }
    fclose(fout);
    printf("Результат успешно записан в out1.txt\n");
}
