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
    int count_left = 0, count_right = 0;

    node_t *headl = NULL, *lastl = NULL;
    node_t *headr = NULL, *lastr = NULL;

    printf("Enter the numbers (0 to complete):\n");
    while (1) {
        scanf("%d", &temp);
        if (temp == 0) break;

        node_t *node = NewNode(temp);

        if (ind % 2 != 0) { 
            count_left++;
            if (headl == NULL) {
                headl = node;
            } else {
                lastl->next = node;
                node->prev = lastl;
            }
            lastl = node;
        } else {
            count_right++;
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

    // Обрезаем длинный список
    if (count_left > count_right) {
        node_t *cur = headl;
        for (int i = 0; i < count_right; i++) {
            cur = cur->next;
        }
        free_list(cur->next);
        cur->next = NULL;
        lastl = cur;
    } else if (count_right > count_left) {
        node_t *cur = headr;
        for (int i = 0; i < count_left; i++) {
            cur = cur->next;
        }
        free_list(cur->next);
        cur->next = NULL;
        lastr = cur;
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

    node_t *current = lastl;
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
                    printf("error: reached the end of the list\n");
                }
                break;

            case 'A': case '4': 
                if (current->prev != NULL) {
                    current = current->prev;
                } else {
                    printf("error: reached the beginning of the list\n");
                }
                break;

            case 'S': 
                free_list(head);
                return 0;

            default:
                printf("error: unknown command\n");
        }
    }

    return 0;
}