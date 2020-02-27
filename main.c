#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int comp = 0;
int mov = 0;

void funcrandom(long long int* a, int n) {              //генерация массива в произвольном порядке
    for (int i = 0; i < n; i++) {
        a[i] = (long long int)rand() * rand() * rand();
    }
}

void funcright(long long int* a, int n) {               //генерация отсортирпованного масива
    int sign;
    for (int i = 0; i < n; i++) {
         if (i == 0) {
             a[i] = (long long int)rand() * rand() * rand();
         } else {
             sign = rand() % 2;
             if (!sign) sign = -1;
             a[i] = (long long int)(labs(a[i - 1]) + (long long int)rand() * rand() % (9223372036854775808 - a[i - 1])) * sign;
         }
    }
}

void funcback(long long int* a, int n) {                //генерация массива, отстортированного в обратном порядке
    int sign;
    for (int i = 0; i < n; i++) {
         if (i == 0) {
             a[i] = (long long int)rand() * rand() * rand();
         } else {
             sign = rand() % 2;
             if (!sign) sign = -1;
             a[i] = (long long int)((labs(a[i - 1]) - (long long int)rand() * rand() % a[i - 1]) * sign);
         }
    }
}

void bubble(long long int* a, int n) {                  //сортировка "пузырек"
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comp++;
            if (labs(a[j]) > labs(a[j + 1])) {
                mov++;
                a[j] += a[j + 1];
                a[j + 1] = a[j] - a[j + 1];
                a[j] = a[j] - a[j + 1];
            }
        }
    }
}

void heapify(long long int* a, int n, int i) {          //построение кучи(просеивание максимального элемента вверх)
    int largest = i;        //максимальный элемент(корень)
    int l = 2 * i + 1;      //индекс левого ребенка
    int r = 2 * i + 2;      //индекс правого ребенка
    if (l < n) {                                        //сравниваем максимальный элемент и левого ребенка
        comp++;
        if (labs(a[l]) > labs(a[largest])) largest = l;
    }
    if (r < n) {                                        //сравниваем максимальный элемент и правого ребенка
        comp++;
        if (labs(a[r]) > labs(a[largest])) largest = r;
    }
    if (largest != i) {                                 //меняем местами максимальный элемент и корень(если они не совпадают)
        mov++;
        a[largest] += a[i];
        a[i] = a[largest] - a[i];
        a[largest] = a[largest] - a[i];
        heapify(a, n, largest);
    }
}
void pyramid(long long int* a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)                //формируем кучу
        heapify(a, n, i);
    for (int i = n - 1; i > 0; i--) {                   //меняем местами корень и последний элемент в куче и выкидываем его из кучи
        mov++;
        a[0] += a[i];
        a[i] = a[0] - a[i];
        a[0] = a[0] - a[i];
        heapify(a, i, 0);                               //опять формируем кучу(просеиваем корень вниз)
    }
}

int main(void) {
    srand(time(NULL));
    printf("1.Bubble:\n");                              //сортировка "пузырек" и вывод данных
    for (int n = 10; n <= 10000; n *= 10) {
        printf("  n = %d\n", n);
        long long int* a = calloc(n, sizeof(long long int));
        funcright(a, n);
        bubble(a, n);
        printf("    1.Items are already put in order: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcback(a, n);
        bubble(a, n);
        printf("    2.Items are put in reverse order: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcrandom(a,n);
        bubble(a, n);
        printf("    3.Items are arranged randomly: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcrandom(a,n);
        bubble(a, n);
        printf("    4.Items are arranged randomly: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        free(a);
    }
    printf("2.Pyramidal sorting:\n");                   //пирамидальная сортировка и вывод данных
    for (int n = 10; n <= 10000; n *= 10) {
        printf("  n = %d\n", n);
        long long int* a = calloc(n, sizeof(long long int));
        funcright(a, n);
        pyramid(a, n);
        printf("    1.Items are already put in order: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcback(a, n);
        pyramid(a, n);
        printf("    2.Items are put in reverse order: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcrandom(a,n);
        pyramid(a, n);
        printf("    3.Items are arranged randomly: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        funcrandom(a,n);
        pyramid(a, n);
        printf("    4.Items are arranged randomly: %d %d\n", comp, mov);
        comp = 0, mov = 0;
        free(a);
    }
    return 0;
}
