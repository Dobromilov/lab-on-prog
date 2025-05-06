# Важно знать!!!

### **1. Основы создания потоков**
- **`pthread_create()`** — создание нового потока:
  ```c
  pthread_create(&tid, NULL, функция_потока, аргументы);
  ```
  - Передача указателя на функцию и аргументов
  - Пример: создание потоков для умножения матриц

- **`pthread_join()`** — ожидание завершения потока:
  ```c
  pthread_join(thread_id, NULL); 
  ```
  - Гарантирует, что главный поток дождется завершения всех рабочих

---

### **2. Передача данных в потоки**
- **Структуры для аргументов**:
  ```c
  typedef struct {
    int start_row;
    int end_row;
    int** A;
    int** B;
    // ...
  } ThreadArgs;
  ```
  - Используются для передачи параметров в поток
  - Пример: передача блоков матриц для умножения

- **Важно**: Данные должны быть *живыми* на момент работы потока (нельзя передавать локальные переменные, которые могут быть уничтожены).

---

### **3. Синхронизация потоков**
- **Мьютексы (`pthread_mutex_t`)**:
  ```c
  pthread_mutex_lock(&mutex);   // Захват
  pthread_mutex_unlock(&mutex); // Освобождение
  ```
  - Защита общих ресурсов от одновременного доступа
  - Пример: синхронизация вывода между потоками

- **Активное ожидание vs блокировка**:
  - В первом примере с выводом: мьютекс блокирует поток до освобождения ресурса

---

### **4. Распределение нагрузки**
- **Разделение работы**:
  ```c
  int rows_per_thread = N / THREADS;
  int remainder = N % THREADS;
  ```
  - Равномерное распределение строк матрицы между потоками
  - Обработка остатка: первые потоки получают на 1 строку больше

- **Локализация данных**:
  - Каждый поток работает только со своим блоком данных (строки матрицы)

---

### **5. Обработка ошибок (что важно добавить!)**
- **Проверка создания потоков**:
  ```c
  if (pthread_create(...) != 0) {
    perror("Ошибка создания потока");
    exit(EXIT_FAILURE);
  }
  ```

- **Проверка выделения памяти**:
  ```c
  if (A == NULL) {
    fprintf(stderr, "Ошибка выделения памяти");
    exit(EXIT_FAILURE);
  }
  ```

---

### **6. Измерение производительности**
- **Точный замер времени**:
  ```c
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  // ... код ...
  clock_gettime(CLOCK_MONOTONIC, &end);
  ```
  - Измерение только времени работы параллельной части

---

### **7. Типичные проблемы потоков**
- **Гонки данных (Race conditions)**:
  - Возникают, когда несколько потоков пишут в одну переменную без синхронизации
  - Решение: мьютексы или атомарные операции

- **Утечки памяти**:
  - Важно освобождать память и уничтожать мьютексы:
  ```c
  pthread_mutex_destroy(&mutex);
  free(matrix);
  ```

---

### **8. Паттерны многопоточности**
- **Worker threads**:
  - Главный поток создает рабочих, распределяет задачи, собирает результаты
  - Пример: умножение матриц, где каждый поток вычисляет свой блок

- **Fork-Join модель**:
  - Параллельное выполнение -> ожидание завершения -> продолжение главного потока

---

# 1). Создание потока
```c
void* child_thread(void* arg) {
    for (int i = 0; i < 5; i++) 
        printf("Child: line %d\n", i+1);
    return NULL;
}

int main(){
    pthread_t thread;
    pthread_create(&thread, NULL, child_thread, NULL);
    for (int i =0; i<5; i++){
        printf("Main: %d\n",i+1);
    }
    pthread_join(thread, NULL);    
}
```
**Что делает:**
- Создаёт один дочерний поток
- Главный и дочерний потоки выводят по 5 строк **параллельно**
- `pthread_join()` гарантирует завершение дочернего потока перед выходом

**Вывод (пример):**
```
Main: 1
Child: line 1
Main: 2
Child: line 2
...
```
*Порядок строк может быть произвольным!*

---

# 2) Ожидание потока (модификация)
```c
int main(){
    pthread_t thread;
    pthread_create(&thread, NULL, child_thread, NULL);
    pthread_join(thread, NULL); // Ожидание завершения дочернего потока
    for (int i =0; i<5; i++){
        printf("Main: %d\n",i+1);
    }
}
```
**Что изменилось:**
- Главный поток **ждёт завершения дочернего** перед своим выводом
- Вывод будет строго последовательным:
  ```
  Child: line 1
  Child: line 2
  ...
  Main: 1
  Main: 2
  ...
  ```

---

# 3) Параметры потока
```c
void* child_thread(void* arg) {
    int id=*(int*)arg;
    for (int i = 0; i < 3; i++) 
        printf("thread: %d line %d\n",id , i+1);
    return NULL;
}

int main(){
    pthread_t thread[N];
    for (int i=0; i<N; i++){
        int id=i+1;
        pthread_create(&thread[i], NULL, child_thread, &id);
    }
    for (int i = 0; i < N; i++) 
        pthread_join(thread[i], NULL);
}
```
**Проблема:**  
Все потоки получат один адрес переменной `id`, которая меняется в цикле. Это приводит к **гонке данных** (race condition).

**Исправление:**  
Нужно выделять отдельную память для каждого потока:
```c
int* id = malloc(sizeof(int));
*id = i+1;
pthread_create(&thread[i], NULL, child_thread, id);
```

---

### 4) Завершение потока без ожидания
```c
void* thread_func(void* arg) {
  int id = *(int*)arg;
  free(arg);
  while(1) {
      printf("Thread %d working\n", id);
      sleep(1);
  }
  return NULL;
}

int main() {
  pthread_t t[N];
  for (int i = 0; i < N; i++) {
      int* arg = malloc(sizeof(int));
      *arg = i+1;
      pthread_create(&t[i], NULL, thread_func, arg);
  }

  sleep(2);
  for (int i = 0; i < 4; i++) 
      pthread_cancel(t[i]);
}
```
**Что делает:**
- Создаёт 4 потока с бесконечным циклом
- Через 2 секунды прерывает их с помощью `pthread_cancel()`
- **Проблема:** Не освобождает ресурсы при отмене

---

# 5) Обработка завершения потока
```c
void* cleanup_p(void* arg){
  int id = *(int*)arg;
  printf("Thread %d exiting\n", id);
  free(arg);
}

void* thread_func(void* arg) {
  pthread_cleanup_push(cleanup_p, arg);
  int id = *(int*)arg;
  free(arg);
  
  while(1) {
      printf("Thread %d working\n", id);
      sleep(1);
  }
  pthread_cleanup_pop(1);
  return NULL;
}
```
**Улучшения:**
- `pthread_cleanup_push()` регистрирует функцию очистки
- При отмене потока автоматически вызывается `cleanup_p()`
- Гарантированное освобождение ресурсов

---

# 6) Sleepsort
```c
void* sleeper(void* arg) {
    int v = *(int*)arg;
    usleep(v);
    printf("%d ", v);
    return NULL;
}

int main() {
    int n, arr[MAXN];
    pthread_t t[MAXN];

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    for (int i = 0; i < n; i++)
        pthread_create(&t[i], NULL, sleeper, &arr[i]);

    for (int i = 0; i < n; i++)
        pthread_join(t[i], NULL);
}
```
**Принцип работы:**
1. Каждое число из массива передаётся в отдельный поток
2. Поток "засыпает" на время, пропорциональное значению числа
3. После сна выводит число
4. Меньшие числа просыпаются раньше → вывод в отсортированном порядке

**Пример:**  
Вход: `[300, 100, 200]`  
Вывод: `100 200 300`

---

### **Общие выводы:**
1. **Создание потоков:** `pthread_create()`
2. **Синхронизация:** `pthread_join()`, `pthread_cancel()`
3. **Передача параметров:** Через указатели, важно избегать гонок
4. **Очистка ресурсов:** `pthread_cleanup_push()/pop()`
5. **Практические паттерны:** Sleepsort, Worker threads


# 7) Синхронизированный вывод родительского и дочернего потоков

Программа демонстрирует синхронизацию двух потоков (родительского и дочернего) с использованием мьютексов для поочерёдного вывода сообщений.

```c
#include <stdio.h>
#include <pthread.h>

// Создаём два мьютекса
pthread_mutex_t m_parent = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_child = PTHREAD_MUTEX_INITIALIZER;

void* child_thread(void* _) {
    for (int i = 1; i < 6; i++) {
        pthread_mutex_lock(&m_child);      // Ждём своей очереди
        printf("Дочер. поток: %d\n", i);
        pthread_mutex_unlock(&m_parent);   // Разрешаем работать родителю
    }
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_mutex_lock(&m_child); // Блокируем дочерний мьютекс заранее
    
    pthread_create(&tid, NULL, child_thread, NULL);

    for (int i = 1; i < 6; i++) {
        pthread_mutex_lock(&m_parent);     // Ждём своей очереди
        printf("Главн. поток: %d\n", i);
        pthread_mutex_unlock(&m_child);    // Разрешаем работать дочернему
    }

    pthread_join(tid, NULL);
    pthread_mutex_destroy(&m_parent);
    pthread_mutex_destroy(&m_child);
}

```

## Особенности
- 🛠️ Чёткое чередование: родитель → дочерний → родитель → ...
- 🔒 Использование двойных мьютексов для синхронизации
- ⏳ Отсутствие активного ожидания (busy waiting)
- 🧩 Простая масштабируемость количества итераций

## Принцип работы
### Инициализация мьютексов
```c
pthread_mutex_t m_parent = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_child = PTHREAD_MUTEX_INITIALIZER;
```
- `m_parent` - контролирует доступ родительского потока
- `m_child` - контролирует доступ дочернего потока

### Алгоритм работы
1. Родительский поток блокирует `m_child` при старте
2. Создаётся дочерний поток, который пытается захватить `m_child` (блокируется)
3. Родительский поток:
   - Захватывает `m_parent` (сразу доступен)
   - Выводит сообщение
   - Освобождает `m_child`
4. Дочерний поток:
   - Получает доступ к `m_child`
   - Выводит сообщение
   - Освобождает `m_parent`
5. Процесс повторяется 5 раз


## Сборка и запуск
```bash
# Компиляция
gcc -pthread sync_threads.c -o sync_threads

# Запуск
./sync_threads
```

## Пример вывода
```
Главн. поток: 1
Дочер. поток: 1
Главн. поток: 2
Дочер. поток: 2
Главн. поток: 3
Дочер. поток: 3
Главн. поток: 4
Дочер. поток: 4
Главн. поток: 5
Дочер. поток: 5
```

## Ключевые функции
| Функция | Описание |
|---------|----------|
| `pthread_mutex_lock()` | Блокировка мьютекса |
| `pthread_mutex_unlock()` | Разблокировка мьютекса |
| `pthread_create()` | Создание нового потока |
| `pthread_join()` | Ожидание завершения потока |

## Особенности реализации
1. **Инициализация мьютексов**
   ```c
   pthread_mutex_init(&m_parent, NULL);
   pthread_mutex_init(&m_child, NULL);
   ```
   Мьютексы инициализируются статически через макрос `PTHREAD_MUTEX_INITIALIZER`.

2. **Стартовая блокировка**
   ```c
   pthread_mutex_lock(&m_child); // Перед созданием дочернего потока
   ```
   Гарантирует, что первым всегда начинает родительский поток.

3. **Цикл синхронизации**
   ```c
   // Родительский поток
   pthread_mutex_lock(&m_parent);
   printf("Главн. поток: %d\n", i);
   pthread_mutex_unlock(&m_child);

   // Дочерний поток
   pthread_mutex_lock(&m_child);
   printf("Дочер. поток: %d\n", i);
   pthread_mutex_unlock(&m_parent);
   ```

# 8) Параллельное умножение матриц с использованием pthreads

Программа реализует параллельное умножение квадратных матриц с использованием POSIX Threads. Работа распределяется между потоками по строкам матриц.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int start_row;
    int end_row;
    int start_col;
    int end_col;
    int N;
    int** A;
    int** B;
    int** C;
} ThreadArgs;

void* umnozhenie(void* args) {
    ThreadArgs* targs = (ThreadArgs*)args;
    for (int i = targs->start_row; i < targs->end_row; i++) {
        for (int j = targs->start_col; j < targs->end_col; j++) {
            targs->C[i][j] = 0;
            for (int k = 0; k < targs->N; k++) {
                targs->C[i][j] += targs->A[i][k] * targs->B[k][j];
            }
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Использование: %s <размер_матрицы> <потоки>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int THREADS = atoi(argv[2]);
    if (THREADS > N*N) THREADS = N*N;

    // Выделение памяти
    int **A = (int**)malloc(N * sizeof(int*));
    int **B = (int**)malloc(N * sizeof(int*));
    int **C = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    // Создание потоков
    pthread_t threads[THREADS];
    ThreadArgs targs[THREADS];
    int rows_per_thread = N / THREADS;
    int remainder = N % THREADS;

    int current_row = 0;
    for (int i = 0; i < THREADS; i++) {
        targs[i].start_row = current_row;
        current_row += rows_per_thread + (i < remainder ? 1 : 0);
        targs[i].end_row = current_row;
        targs[i].N = N;
        targs[i].A = A;
        targs[i].B = B;
        targs[i].C = C;
        pthread_create(&threads[i], NULL, umnozhenie, &targs[i]);
    }

    // Ожидание завершения
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Вывод результатов
    if (N < 5) {
        printf("Матрица A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) printf("%d ", A[i][j]);
            printf("\n");
        }
        // Аналогично для B и C
    }

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    return 0;
}

```

## Особенности
- 🚀 Параллельное вычисление с разделением матрицы на блоки строк
- 🔢 Поддержка произвольного размера матриц (N x N)
- 🧮 Автоматическое ограничение числа потоков до N²
- 📊 Вывод результатов для матриц малого размера (N < 5)
- 🧵 Оптимальное распределение нагрузки между потоками

## Сборка и запуск
```bash
# Компиляция с поддержкой pthread
gcc -pthread matrix_mult.c -o matrix_mult

# Запуск с параметрами:
# <размер_матрицы> - целое число > 0
# <потоки> - количество потоков (1 ≤ threads ≤ N²)
./matrix_mult 4 2
```

## Пример вывода (для N=3)
```
Матрица A:
1 1 1 
1 1 1 
1 1 1 

Матрица B:
1 1 1 
1 1 1 
1 1 1 

Результирующая матрица C:
3 3 3 
3 3 3 
3 3 3 
```

## Архитектура
### Структура данных
```c
typedef struct {
    int start_row;    // Начальная строка блока
    int end_row;      // Конечная строка блока
    int N;            // Размер матрицы
    int** A;          // Матрица A
    int** B;          // Матрица B
    int** C;          // Результирующая матрица
} ThreadArgs;
```

### Алгоритм работы
1. Инициализация матриц A и B единицами
2. Распределение строк матрицы между потоками:
   - Каждый поток обрабатывает блок строк размером N/THREADS
   - Остаток строк распределяется по одному первым потокам
3. Параллельное вычисление:
   ```c
   C[i][j] = Σ(A[i][k] * B[k][j]), 0 ≤ k < N
   ```
4. Синхронизация потоков через pthread_join
5. Вывод результатов (для N < 5)

## Ключевые функции
| Функция | Описание |
|---------|----------|
| `umnozhenie()` | Вычисление блока матрицы C |
| `pthread_create()` | Создание рабочих потоков |
| `pthread_join()` | Ожидание завершения потоков |

## Оптимизации
1. **Локальность данных**: Каждый поток работает со своим блоком строк
2. **Балансировка нагрузки**: Равномерное распределение строк с учетом остатка
3. **Экономия памяти**: Освобождение ресурсов после вычислений

## Ограничения
- Максимальный размер матрицы: 2500x2500 (настраивается)
- Тип данных: целые числа (int)
- Нет поддержки GPU-ускорения


# 9) Параллельное умножение матриц с замером времени

Программа реализует параллельное умножение квадратных матриц с точным замером времени выполнения. Оптимизирована для исследования масштабируемости на многопроцессорных системах.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int start_row;
    int end_row;
    int N;
    int** A;
    int** B;
    int** C;
} ThreadArgs;

void* umnozhenie(void* args) {
    ThreadArgs* targs = (ThreadArgs*)args;
    for (int i = targs->start_row; i < targs->end_row; i++) {
        for (int j = 0; j < targs->N; j++) {
            targs->C[i][j] = 0;
            for (int k = 0; k < targs->N; k++) {
                targs->C[i][j] += targs->A[i][k] * targs->B[k][j];
            }
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <matrix_size> <threads>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int THREADS = atoi(argv[2]);
    THREADS = (THREADS > N) ? N : THREADS; // Ограничение потоков

    // Выделение памяти
    int **A = (int**)malloc(N * sizeof(int*));
    int **B = (int**)malloc(N * sizeof(int*));
    int **C = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    // Настройка потоков
    pthread_t threads[THREADS];
    ThreadArgs targs[THREADS];
    int rows_per_thread = N / THREADS;
    int remainder = N % THREADS;
    int current_row = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); // Точный замер времени

    for (int i = 0; i < THREADS; i++) {
        targs[i].start_row = current_row;
        current_row += rows_per_thread + (i < remainder ? 1 : 0);
        targs[i].end_row = current_row;
        targs[i].N = N;
        targs[i].A = A;
        targs[i].B = B;
        targs[i].C = C;
        pthread_create(&threads[i], NULL, umnozhenie, &targs[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time = (end.tv_sec - start.tv_sec) + 
                 (end.tv_nsec - start.tv_nsec) / 1e9;

    // Очистка памяти
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    printf("%.6f\n", time); // Форматированный вывод
    return 0;
}

```

## Особенности
- ⏱️ Точный замер времени выполнения с использованием `clock_gettime()`
- 🧮 Автоматическая балансировка нагрузки между потоками
- 🚫 Ограничение максимального числа потоков размером матрицы
- 📉 Оптимизированное управление памятью
- 🔢 Поддержка матриц произвольного размера

## Сборка и использование
```bash
# Компиляция с поддержкой pthreads
gcc -O3 -pthread matrix_mult.c -o matrix_mult

# Запуск с параметрами:
# <matrix_size> - размер матрицы (N x N)
# <threads> - количество потоков
./matrix_mult 1000 4
```

## Ключевые компоненты
### Структура данных
```c
typedef struct {
    int start_row;    // Начальная строка блока
    int end_row;      // Конечная строка блока
    int N;            // Размер матрицы
    int** A;          // Указатель на матрицу A
    int** B;          // Указатель на матрицу B 
    int** C;          // Указатель на результирующую матрицу
} ThreadArgs;
```

### Алгоритм работы
1. Инициализация матриц:
   - Все элементы A и B заполняются единицами
   - Матрица C инициализируется нулями

2. Распределение задач:
   ```c
   rows_per_thread = N / THREADS;
   remainder = N % THREADS;
   ```
   - Первые `remainder` потоков получают на 1 строку больше

3. Параллельное вычисление:
   - Каждый поток вычисляет свой блок строк матрицы C
   - Формула: `C[i][j] = Σ(A[i][k] * B[k][j])` для 0 ≤ k < N

4. Синхронизация:
   - Главный поток ожидает завершения всех worker-потоков

5. Замер времени:
   - Используется монотонное время CLOCK_MONOTONIC
   - Точность до наносекунд

## Оптимизации
1. **Локализация данных**: Каждый поток работает только со своим блоком строк
2. **Предсказуемое выделение памяти**: Линейное хранение матриц
3. **Балансировка нагрузки**: Равномерное распределение строк + обработка остатка
4. **Векторизация**: Внутренний цикл может быть оптимизирован компилятором

## Ограничения
- Максимальный размер матрицы ограничен доступной памятью
- Тип данных фиксирован (int)
- Нет проверки ошибок выделения памяти


```python
import matplotlib.pyplot as plt

x=[0, 16, 256, 1000, 1700,2500]
y1=[0, 0.000305, 0.082239, 5.490029, 34.863328,158.239867,]
y2=[0,0.000400,0.042056,2.528819,15.982726,75.219546]
y3=[0,0.000564,0.048222,1.230541,4.469586,19.826122]
y4=[0,0.001988,0.043858,1.042493,3.284425,14.604082]
y5=[0,0.013242,0.046186,0.994964,3.094185,14.312091]
fig, ax = plt.subplots()

ax.plot(x, y1, label='1')

ax.plot(x, y2, label='2')
ax.plot(x, y3, label='8')
ax.plot(x, y4, label='32')
ax.plot(x, y5, label='128')

ax.legend()
plt.show()
```
![image](https://github.com/user-attachments/assets/732daa57-bc3e-4e92-a051-3fdd7866aec4)
