### Задание 1

#### Исходный код:
```c
#include <stdio.h>
#include <stdlib.h>

void init(int* arr, int n) {
    arr = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; ++i) {
        arr[i] = i;
    }
}

int main() {
    int* arr = NULL;
    int n = 10;
    init(arr, n);
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    return 0;
}
```

#### Ошибка:
- В функции `init` выделяется память для массива, но указатель `arr` передается по значению, поэтому изменения не сохраняются в `main`.

#### Исправление:
- Нужно передавать указатель на указатель (`int** arr`), чтобы изменения сохранялись.

#### Исправленный код:
```c
#include <stdio.h>
#include <stdlib.h>

void init(int** arr, int n) {
    *arr = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; ++i) {
        (*arr)[i] = i;
    }
}

int main() {
    int* arr = NULL;
    int n = 10;
    init(&arr, n);
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr); // Освобождаем память
    return 0;
}
```

---

### Задание 2

#### Исходный код:
```c
#include <stdio.h>

typedef struct {
    char str[3];
    int num;
} NumberRepr;

void format(NumberRepr* number) {
    sprintf(number->str, "%3d", number->num);
}

int main() {
    NumberRepr number = { .num = 1025 };
    format(&number);
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}
```

#### Ошибка:
- Массив `str` имеет размер 3, но число `1025` требует 4 символа (включая завершающий нулевой символ `\0`).

#### Исправление:
- Увеличим размер массива `str` до 5.

#### Исправленный код:
```c
#include <stdio.h>

typedef struct {
    char str[5]; // Увеличиваем размер массива
    int num;
} NumberRepr;

void format(NumberRepr* number) {
    sprintf(number->str, "%3d", number->num);
}

int main() {
    NumberRepr number = { .num = 1025 };
    format(&number);
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}
```

---

### Задание 3

#### Исходный код:
```c
#include <stdio.h>

#define SQR(x) x * x

int main() {
    int y = 5;
    int z = SQR(y + 1);
    printf("z = %d\n", z);
    return 0;
}
```

#### Ошибка:
- Макрос `SQR(x)` раскрывается в `x * x`, что приводит к неправильному вычислению: `y + 1 * y + 1` вместо `(y + 1) * (y + 1)`.

#### Исправление:
- Добавим скобки вокруг аргумента макроса.

#### Исправленный код:
```c
#include <stdio.h>

#define SQR(x) ((x) * (x)) // Добавляем скобки

int main() {
    int y = 5;
    int z = SQR(y + 1);
    printf("z = %d\n", z);
    return 0;
}
```

---

### Задание 4

#### Исходный код:
```c
#include <stdio.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int* array, int size) {
    int i, j;
    for (i = 0; i < size - 1; ++i) {
        for (j = 0; j < size - i; ++j) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

int main() {
    int array[100] = {10, 15, 5, 4, 21, 7};
    bubble_sort(array, 6);
    int i;
    for (i = 0; i < 6; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
```

#### Ошибка:
- Во внутреннем цикле `j` доходит до `size - i`, что приводит к выходу за границы массива при `j + 1`.

#### Исправление:
- Исправим условие внутреннего цикла на `j < size - i - 1`.

#### Исправленный код:
```c
#include <stdio.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int* array, int size) {
    int i, j;
    for (i = 0; i < size - 1; ++i) {
        for (j = 0; j < size - i - 1; ++j) { // Исправляем условие
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

int main() {
    int array[100] = {10, 15, 5, 4, 21, 7};
    bubble_sort(array, 6);
    int i;
    for (i = 0; i < 6; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
```

---

### Итог:
1. **Задание 1**: Исправлена передача указателя на указатель.
2. **Задание 2**: Увеличен размер массива `str`.
3. **Задание 3**: Добавлены скобки в макрос `SQR`.
4. **Задание 4**: Исправлено условие внутреннего цикла в сортировке пузырьком.
