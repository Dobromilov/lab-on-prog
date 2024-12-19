#include <stdio.h>
#include <stdlib.h>

int main() {
    int max_gold_kg;
    scanf("%d", &max_gold_kg);
    int counter;
    scanf("%d", &counter);
    int gold_bars[counter];
    for (int i = 0; i < counter; i++) {
        scanf("%d", &gold_bars[i]);
    }

    int array[max_gold_kg + 1];
    for (int i = 0; i <= max_gold_kg; i++) {
        array[i] = 0; 
    }

    for (int i = 0; i < counter; i++) {
        for (int w = max_gold_kg; w >= gold_bars[i]; w--) {
            if (array[w - gold_bars[i]] + gold_bars[i] > array[w]) {
                array[w] = array[w - gold_bars[i]] + gold_bars[i];
            }
        }
    }
    printf("%d\n", array[max_gold_kg]);

    return 0;
}