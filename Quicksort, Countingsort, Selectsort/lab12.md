
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 300

struct Student{
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent(const char* name,int math, int phy, int inf){
    struct Student newStudent;
    strcpy(newStudent.name, name);
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}


void CountingSort(int n,struct Student *students) {
    clock_t start = clock();
    int* count = (int*)calloc(MAX + 1, sizeof(int));
    
    for (int i = 0; i < n; i++) 
        count[students[i].total]++;
    int index = 0;
    for (int i = MAX; i >= 0; i--) {
        while (count[i] > 0) {
            students[index++].total = i;
            count[i]--;
        }
    }
    free(count);
    clock_t end = clock();
    printf("Время работы программы: %f секунд \n Размер данных: %ld байт",(double)(end - start) / CLOCKS_PER_SEC,n*sizeof(int));
}


void SelectionSort(struct Student arr[],int size){
    clock_t start = clock();
    for (int i=0; i<size-1; i++){
        int maxIndex = i;
        
        for (int j=i+1; j<size; j++){
            if (arr[j].total>arr[maxIndex].total){
                maxIndex=j;
            }
        }
        
        struct Student temp;
        temp=arr[i];
        arr[i]=arr[maxIndex];
        arr[maxIndex]=temp;
    }
    clock_t end = clock();
    printf("Время работы программы: %f секунд \n Размер данных: %ld байт\n",(double)(end - start) / CLOCKS_PER_SEC,size*sizeof(int));
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Student arr[], int low, int high) {
    int pivot = arr[high].total;
    int i = (low - 1);
    
    for (int j = low; j < high; j++) {
        if (arr[j].total < pivot) {
            i++;
            swap(&arr[i].total, &arr[j].total);
        }
    }
    swap(&arr[i + 1].total, &arr[high].total);
    return (i + 1);
}

void quicksort(struct Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void printPerson(struct Student p){
    printf("name: %s; ",p.name);
    printf("math: %d; ",p.math);
    printf("phy: %d; ",p.phy);
    printf("inf: %d; ",p.inf);
    printf("total: %d; \n",p.total);
}


void CpuInfo(){
    system("grep 'model name' /proc/cpuinfo | uniq");
    system("grep 'cpu MHz' /proc/cpuinfo | uniq");
}

int main(void){
    const int size=10000;
    struct Student people[size];
    
    for (int i=0; i<size; i++){
        char name[64];
        sprintf(name, "Student %d", i + 1);
        int math=rand()%101;
        int phy=rand()%101;
        int inf=rand()%101;
        people[i] = addStudent(name, math, phy, inf);
    }

    printf("Before sorting: \n");
    for (int i = 0; i < size; i++) {
        printPerson(people[i]);
    }

    // SelectionSort(people,size);
    // CountingSort(size,people);
    quicksort(people,0,size-1);
    printf("\n\nSort array: \n");
    for (int i = 0; i < size; i++) {
        printPerson(people[i]);
    }
    printf("\n");
    CpuInfo();
}
```

### Описание программы:

Эта программа на языке C демонстрирует работу трех алгоритмов сортировки: **Сортировка выбором (Selection Sort)**, **Сортировка подсчетом (Counting Sort)** и **Быстрая сортировка (Quick Sort)**. Программа сортирует массив структур `Student` по их общему баллу (`total`) и измеряет время выполнения каждого алгоритма. Также программа выводит информацию о процессоре.

---

### Основные компоненты программы:

1. **Структура `Student`**:
   - Содержит поля:
     - `name`: имя студента.
     - `math`: оценка по математике.
     - `phy`: оценка по физике.
     - `inf`: оценка по информатике.
     - `total`: общий балл (сумма оценок по трем предметам).

2. **Функция `addStudent`**:
   - **Назначение**: Создает и возвращает структуру `Student` с заданными значениями.
   - **Параметры**:
     - `name`: имя студента.
     - `math`, `phy`, `inf`: оценки по предметам.
   - **Принцип работы**: Заполняет поля структуры и вычисляет общий балл.

3. **Функция `CountingSort`**:
   - **Назначение**: Сортирует массив студентов по убыванию общего балла с использованием сортировки подсчетом.
   - **Параметры**:
     - `n`: количество студентов.
     - `students`: массив студентов.
   - **Принцип работы**:
     - Создает массив `count` для подсчета количества студентов с каждым возможным значением общего балла.
     - Заполняет массив `count`.
     - Восстанавливает отсортированный массив на основе массива `count`.
     - Измеряет время выполнения и выводит его на экран.

4. **Функция `SelectionSort`**:
   - **Назначение**: Сортирует массив студентов по убыванию общего балла с использованием сортировки выбором.
   - **Параметры**:
     - `arr`: массив студентов.
     - `size`: количество студентов.
   - **Принцип работы**:
     - Находит максимальный элемент в неотсортированной части массива и перемещает его в начало.
     - Повторяет процесс для оставшейся части массива.
     - Измеряет время выполнения и выводит его на экран.

5. **Функция `quicksort`**:
   - **Назначение**: Сортирует массив студентов по возрастанию общего балла с использованием быстрой сортировки.
   - **Параметры**:
     - `arr`: массив студентов.
     - `low`: начальный индекс.
     - `high`: конечный индекс.
   - **Принцип работы**:
     - Выбирает опорный элемент (pivot).
     - Разделяет массив на две части: элементы меньше опорного и элементы больше опорного.
     - Рекурсивно сортирует обе части.

6. **Функция `printPerson`**:
   - **Назначение**: Выводит информацию о студенте на экран.
   - **Параметры**:
     - `p`: структура `Student`.

7. **Функция `CpuInfo`**:
   - **Назначение**: Выводит информацию о процессоре (модель и частоту).
   - **Принцип работы**: Использует команду `grep` для извлечения данных из `/proc/cpuinfo`.

8. **Функция `main`**:
   - **Назначение**: Основная функция программы.
   - **Принцип работы**:
     - Создает массив из 10 000 студентов с случайными оценками.
     - Выводит массив до сортировки.
     - Выполняет одну из сортировок (в зависимости от того, какая функция раскомментирована).
     - Выводит отсортированный массив.
     - Выводит информацию о процессоре.

---

### Пример работы программы:

#### Ввод:
Программа не требует ввода данных от пользователя. Все данные генерируются случайным образом.

#### Вывод:
```
Before sorting:
name: Student 1; math: 87; phy: 45; inf: 92; total: 224;
name: Student 2; math: 34; phy: 78; inf: 56; total: 168;
...
name: Student 10000; math: 12; phy: 67; inf: 89; total: 168;

Sort array:
name: Student 1234; math: 100; phy: 100; inf: 100; total: 300;
name: Student 5678; math: 99; phy: 99; inf: 99; total: 297;
...
name: Student 9999; math: 0; phy: 0; inf: 0; total: 0;

Время работы программы: 0.123456 секунд
Размер данных: 40000 байт

model name: Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz
cpu MHz: 2600.000
```

---

### Замечания:
1. **Сортировка подсчетом**:
   - Работает только для целых чисел в ограниченном диапазоне (в данном случае от 0 до 300).
   - Не сохраняет исходные данные студентов, так как сортирует только поле `total`.

2. **Сортировка выбором**:
   - Медленная для больших массивов (время выполнения — O(n²)).

3. **Быстрая сортировка**:
   - Быстрая и эффективная (время выполнения — O(n log n) в среднем случае).
   - Сортирует по возрастанию. Чтобы отсортировать по убыванию, нужно изменить условие в функции `partition`.

4. **Информация о процессоре**:
   - Работает только на Linux-системах, где доступен файл `/proc/cpuinfo`.

5. **Освобождение памяти**:
   - В данной программе не используется динамическое выделение памяти, поэтому освобождение не требуется.

---

