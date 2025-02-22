```c
//номер 5
#include <stdio.h>
int main() {
        int h;
        scanf("%d", &h);
        int count1=h,count=0;
        while (count1>=0) {
                for (int i = 0,c=1; i < h - count1-c; i++) {
                        printf(" ");
                        c+=1;
                }
                for (int i = 0; i < count1; i++) {
                        printf("o");
                }
        if (count1 == 2) {
            printf("\n");
            break;
        } else {
            printf("\n");
        }
        count1-=2;
    }
    if (h%2==0) {
            count=4;
        } else {
            count=3;
        }
    while (count<=h) {
        for (int i = 0; i < (h - count) / 2; i++){
            printf(" ");
        }
        for (int i=0; i!=count;i++){
            printf("o");
        }
        printf("\n");
        count+=2;
    }
}
```
