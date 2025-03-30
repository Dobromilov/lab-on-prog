# Описание проекта: Система управления данными о поездах

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRAIN_COUNT 5

typedef struct {
    char destination[50];    
    int number;
    int time[2];    
} Train;

void saveSingleTrain() {
    Train t[TRAIN_COUNT] = {
                    {"Москва", 123, {14, 30}},
                    {"Санкт-Питербург", 1365, {19, 50}},
                    {"Новосибирск", 498, {21, 40}},
                    {"Бийск", 201, {22, 30}},
                    {"Барнаул", 765, {2, 00}}
                };
    
    FILE *file = fopen("Train.dat","wb");
    if (!file){
        printf("Файл не найден!");
        return;
    }

    size_t write = fwrite(t, sizeof(Train),TRAIN_COUNT,file);
    if (write != 5) {
        printf("Ошибка записи!\n");
    }
    
    fclose(file);
    printf("Поезд успешно сохранён!\n");
}

void readTrains(){
    FILE *file = fopen("Train.dat","rb");
    if (!file){
        printf("Файл не найден!");
        return;
    }
    
    fseek(file,0,SEEK_END); // переместил указатель в конец, чтоб после вычислить
                            // кол-во байт
    long fileSize=ftell(file); // ftell() возвращает текущую позицию указателя
                               // поскольку мы в конце файла, это даёт нам размер файла в байтах
    rewind(file);
    int count=fileSize/sizeof(Train);
    Train *trains=malloc(fileSize);
    fread(trains, sizeof(Train), count, file);

    printf("\nСписок рейсов: \n");
    printf("--------------------------------------------\n");

    for (int i=0; i<count;i++){
        printf("%d\t%-15s\t%d\t%02d:%02d\n", 
            i+1,
            trains[i].destination, 
            trains[i].number, 
            trains[i].time[0], 
            trains[i].time[1]);
    }
    free(trains);
    fclose(file);
}  

void searchTrains(){
    char search[50];
    printf("Введите пункт назначения: ");
    scanf("%49s",search);
    
    FILE *file = fopen("Train.dat","rb");
    if (!file){
        printf("Файл не найден!");
        return;
    }
    Train t;
    int found = 0;
    
    printf("\nРезультаты поиска:\n");
    printf("--------------------------------------------\n");

    while (fread(&t, sizeof(Train), 1, file) == 1) {
        if (strcmp(t.destination, search) == 0) {
            printf("%-15s\t%d\t%02d:%02d\n",
                   t.destination,
                   t.number,
                   t.time[0],
                   t.time[1]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Поездов в '%s' не найдено.\n", search);
    }
    
    fclose(file);
}

int main() {
    int choice;
    printf("\nУправление базой поездов:\n");
    printf("1. Создать/перезаписать данные\n");
    printf("2. Показать все поезда\n");
    printf("3. Поиск по пункту назначения\n");
    printf("Выберите действие: ");
    scanf("%d", &choice);
    switch (choice){
    case 1:
        saveSingleTrain();
        break;
    case 2:
        readTrains();
        break;
    case 3:
        searchTrains();
        break;
    default:
        printf("Ошибка ввода!");
        break;
    }
    return 0;
}
```

## 🚂 Обзор
Программа для работы с расписанием поездов, реализующая:
- Хранение данных в бинарных файлах
- Просмотр всего расписания
- Поиск поездов по пункту назначения
- Простое консольное меню

## 📋 Функциональность
- **Структура данных**:
  ```c
  typedef struct {
      char destination[50];    // Пункт назначения
      int number;              // Номер поезда
      int time[2];             // Время отправления [часы, минуты]
  } Train;
  ```

- **Основные операции**:
  - Запись массива поездов в бинарный файл
  - Чтение данных из файла с автоматическим определением количества записей
  - Поиск по пункту назначения

## 🛠 Технические особенности
1. **Работа с файлами**:
   - Использование бинарного формата для эффективного хранения
   - Функции `fseek`, `ftell` для определения размера файла
   - Динамическое выделение памяти под данные

2. **Реализованные функции**:
   ```c
   void saveSingleTrain();     // Сохранение данных
   void readTrains();          // Чтение и вывод всех поездов
   void searchTrains();        // Поиск по пункту назначения
   ```

## 🚀 Как использовать
1. Скомпилируйте программу:
   ```bash
   gcc trains.c -o trains
   ```
2. Запустите:
   ```bash
   ./trains
   ```
3. Выберите действие в меню:
   - 1: Создать/перезаписать данные
   - 2: Показать все поезда
   - 3: Найти поезда по пункту назначения
   - 4: Выход

## 📌 Пример работы
```
Управление базой поездов:
1. Создать/перезаписать данные
2. Показать все поезда
3. Поиск по пункту назначения
4. Выход
Выберите действие: 2

Список поездов:
Список рейсов: 
--------------------------------------------
1       Москва          123     14:30
2       Санкт-Питербург 1365    19:50
3       Новосибирск     498     21:40
4       Бийск           201     22:30
5       Барнаул         765     02:00
```

## 📈 Возможные улучшения
- Добавление поиска по номеру поезда и времени
- Редактирование существующих записей
- Валидация вводимых данных
- Графический интерфейс
