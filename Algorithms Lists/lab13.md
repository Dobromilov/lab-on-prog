# Односвязный список на языке C

```c
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *NewNode(int data){
    struct Node *NewNode=(struct Node*)malloc(sizeof(struct Node));
    NewNode->data=data;
    NewNode->next=NULL;

    return NewNode;
}

void free_list(struct Node *head){
    struct Node *cur=head;
    while (cur != NULL){
        struct Node *next = cur->next;
        free(cur);
        cur=next;
    }
}


void print_list(struct Node *head){
    struct Node *cur=head;
    while (cur != NULL){
        printf("%d ",cur->data);
        cur=cur->next;
    }
}

int main(void){
    typedef struct Node node_t;
    int temp;
    node_t *head = NULL;  // Голова списка
    node_t *last = NULL;  // Последний узел списка

    printf("Введите числа (0 для завершения):\n ");
    while (1) {
        scanf("%d", &temp);
        if (temp != 0) {
            node_t *node = NewNode(temp);
            if (head == NULL) {
                head = node;
            } else {
                last->next = node;
            }
            last = node;
        } else {
            break;
        }
    }

    printf("Список: ");
    print_list(head);
    free_list(head);

    return 0;
}
```


Это простая реализация односвязного списка на языке C. Программа позволяет:
1. Создавать список из целых чисел, вводимых пользователем.
2. Выводить список на экран.
3. Корректно освобождать память после использования списка.

## Как работает программа

1. Пользователь вводит целые числа. Ввод завершается, когда вводится `0`.
2. Каждое введённое число добавляется в конец списка.
3. После завершения ввода программа выводит весь список на экран.
4. В конце программа освобождает всю выделенную память.

## Структура программы

- **`struct Node`**: Структура, представляющая узел списка. Каждый узел содержит:
  - `int data` — целое число (данные узла).
  - `struct Node *next` — указатель на следующий узел в списке.

- **Функции**:
  - `struct Node* NewNode(int data)` — создаёт новый узел с заданным значением.
  - `void print_list(struct Node *head)` — выводит список на экран.
  - `void free_list(struct Node *head)` — освобождает память, выделенную для списка.

## Пример использования

1. Скомпилируйте программу:
   ```bash
   gcc -o linked_list linked_list.c
   ```

2. Запустите программу:
   ```bash
   ./linked_list
   ```

3. Введите числа (например, `1 2 3 0`):
   ```
   Введите числа (0 для завершения):
   1
   2
   3
   0
   ```

4. Программа выведет:
   ```
   Список: 1 2 3
   ```

## Как это работает

1. **Создание списка**:
   - Пользователь вводит числа, которые добавляются в конец списка.
   - Если список пуст, новый узел становится головой списка.
   - Иначе новый узел добавляется после последнего узла.

2. **Вывод списка**:
   - Программа проходит по всем узлам списка, начиная с головы, и выводит их данные.

3. **Освобождение памяти**:
   - Программа проходит по всем узлам списка и освобождает память, выделенную для каждого узла.

## Зависимости

- Компилятор C (например, `gcc`).

# Двусвязный список на языке C

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *prev;
    int data;
    struct Node *next;
};

// Функция создания нового узла
struct Node *NewNode(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Функция освобождения памяти списка
void free_list(struct Node *head) {
    struct Node *cur = head;
    while (cur != NULL) {
        struct Node *next = cur->next;
        free(cur);
        cur = next;
    }
}

// Функция печати списка
void print_list(struct Node *head) {
    struct Node *cur = head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int main(void) {
    typedef struct Node node_t;
    int temp, ind = 1;

    node_t *headl = NULL, *lastl = NULL;
    node_t *headr = NULL, *lastr = NULL;

    printf("Enter the numbers (0 to complete):\n");
    while (1) {
        scanf("%d", &temp);
        if (temp == 0) break;

        node_t *node = NewNode(temp);

        if (ind % 2 != 0) { 
            if (headl == NULL) {
                headl = node;
            } else {
                lastl->next = node;
                node->prev = lastl;
            }
            lastl = node;
        } else {
            if (headr == NULL) {
                headr = node;
            } else {
                lastr->next = node;
                node->prev = lastr;
            }
            lastr = node;
        }

        ind++;
    }

    printf("left: ");
    print_list(headl);

    printf("right: ");
    print_list(headr);

    if (lastl != NULL && headr != NULL) {
        lastl->next = headr;
        headr->prev = lastl;
    }

    node_t *head = headl ? headl : headr;

    node_t *current = head;
    char command;

    printf("D/6 - forward, A/4 - back, S - exit\n");

    while (1) {
        printf("The current element: %d\n", current->data);
        printf("Command: \n");
        scanf(" %c", &command);

        switch (command) {
            case 'D': case '6': 
                if (current->next != NULL) {
                    current = current->next;
                } else {
                    printf("error\n");
                }
                break;

            case 'A': case '4': 
                if (current->prev != NULL) {
                    current = current->prev;
                } else {
                    printf("error\n");
                }
                break;

            case 'S': 
                free_list(head);
                return 0;

            default:
                printf("Нerror\n");
        }
    }

    return 0;
}

```

Это реализация двусвязного списка на языке C с дополнительными функциями для разделения списка на два подсписка (левый и правый) и навигации по списку с помощью команд. Программа позволяет:
1. Создавать двусвязный список из целых чисел, вводимых пользователем.
2. Разделять список на два подсписка: левый (нечётные позиции) и правый (чётные позиции).
3. Выводить левый и правый подсписки на экран.
4. Объединять подсписки в один двусвязный список.
5. Навигация по списку с помощью команд: вперёд, назад и выход.
6. Корректно освобождать память после использования списка.

## Как работает программа

1. Пользователь вводит целые числа. Ввод завершается, когда вводится `0`.
2. Каждое введённое число добавляется в один из двух подсписков:
   - Левый подсписок: числа на нечётных позициях (1, 3, 5, ...).
   - Правый подсписок: числа на чётных позициях (2, 4, 6, ...).
3. После завершения ввода программа выводит левый и правый подсписки на экран.
4. Подсписки объединяются в один двусвязный список.
5. Пользователь может перемещаться по списку с помощью команд:
   - `D` или `6`: переход к следующему элементу.
   - `A` или `4`: переход к предыдущему элементу.
   - `S`: завершение программы.
6. В конце программа освобождает всю выделенную память.

## Структура программы

- **`struct Node`**: Структура, представляющая узел двусвязного списка. Каждый узел содержит:
  - `int data` — целое число (данные узла).
  - `struct Node *prev` — указатель на предыдущий узел.
  - `struct Node *next` — указатель на следующий узел.

- **Функции**:
  - `struct Node* NewNode(int data)` — создаёт новый узел с заданным значением.
  - `void print_list(struct Node *head)` — выводит список на экран.
  - `void free_list(struct Node *head)` — освобождает память, выделенную для списка.

- **Основная логика**:
  - Разделение списка на левый и правый подсписки.
  - Объединение подсписков в один двусвязный список.
  - Навигация по списку с помощью команд.

## Пример использования

1. Скомпилируйте программу:
   ```bash
   gcc -o doubly_linked_list doubly_linked_list.c
   ```

2. Запустите программу:
   ```bash
   ./doubly_linked_list
   ```

3. Введите числа (например, `1 2 3 4 5 0`):
   ```
   Enter the numbers (0 to complete):
   1
   2
   3
   4
   5
   0
   ```

4. Программа выведет:
   ```
   left: 1 3 5
   right: 2 4
   ```

5. Навигация по списку:
   ```
   The current element: 1
   Command:
   D
   The current element: 2
   Command:
   A
   The current element: 1
   Command:
   S
   ```

6. Программа завершит работу и освободит память.

## Как это работает

1. **Создание списка**:
   - Пользователь вводит числа, которые добавляются в левый или правый подсписок в зависимости от их позиции.
   - Если подсписок пуст, новый узел становится его головой.
   - Иначе новый узел добавляется после последнего узла подсписка.

2. **Вывод подсписков**:
   - Программа проходит по всем узлам левого и правого подсписков и выводит их данные.

3. **Объединение подсписков**:
   - Левый и правый подсписки объединяются в один двусвязный список.

4. **Навигация по списку**:
   - Пользователь может перемещаться по списку с помощью команд `D` (вперёд), `A` (назад) и `S` (выход).

5. **Освобождение памяти**:
   - Программа проходит по всем узлам списка и освобождает память, выделенную для каждого узла.

## Зависимости

- Компилятор C (например, `gcc`).

## Как использовать этот код

1. Склонируйте репозиторий или добавьте этот код в свой проект.
2. Скомпилируйте программу с помощью команды:
   ```bash
   gcc -o doubly_linked_list doubly_linked_list.c
   ```
3. Запустите программу:
   ```bash
   ./doubly_linked_list
   ```
