```c
// Пусть имеется некоторое натуральное число n. Проверить, является ли оно степенью числа 2, 
//то есть найдется ли такое целое неотрицательное число k, что n = 2k.

#include <stdio.h>

int degree(int n) {
    for (int i=1,c=2; i<32; i+=1){
        if (n==0){
            return 0;
        } else {
            if (n == c << 1) {
                return i+1;
            } 
        }
        c=c<<1;
    }
    return -1;
}

int main() {
    int n,k;
    scanf("%d",&n);
    k=degree(n);
    printf("%d\n",k);
}
```

```c
// Найти количество единичных битов в целом неотрицательном числе a.

#include <stdio.h>

int count(int n) {
    int count=0;
    while (n) {
        count+=n&1;
        n>>=1;
    }
    return count;
}

int main() {
    int n,k;
    scanf("%d",&n);
    k=count(n);
    printf("%d\n",k);
}
```
