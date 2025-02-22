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
    printf("Введите числа (0 для завершения):\n ");
    printf("Список: ");
    print_list(head);
    free_list(head);

    return 0;
}
```
# Односвязный список на языке C

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

