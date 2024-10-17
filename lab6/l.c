// //4
// #define N 5
// #include <stdio.h>

// void print_array(int n, int array[n]) {
//     printf("mas: ");
//     for (int i = 0; i < n; i++) {
//         printf("%d ", array[i]);
//     }
//     printf("\n");
// }

// int mx_array(int n, int array[]) {
//     int mx = array[0]; 
//     for (int i = 1; i < n; i++) {
//         if (mx < array[i]) {
//             mx = array[i];
//         }
//     }
//     return mx;
// }

// int count_array(int n, int array[]) {
//     int count = 0;
//     for (int i = 0; i < n; i++) {
//         if (array[i] < 0) { 
//             count++;
//         }
//     }
//     return count;
// }

// int suco_array(int n, int array[]) {
//     int sum=0, count=0;
//     for (int i = 0; i < n; i++) {
//         sum+=array[i];
//         count+=1;
//     }
//     return sum/count;
// }

// int main() {
//     int a[N] = {-1, 2, 3, -4, -5};
//     int b[N] = {6, 7, -8, 9, 0};
//     int c[N] = {0};

//     for (int i = 0; i < N; i++) {
//         c[i] = b[i] + a[i];
//     }
//     printf("a: ");
//     print_array(N, a);
//     printf("b: ");
//     print_array(N, b);
//     printf("c: ");
//     print_array(N, c);

//     float average=suco_array(N,c);

//     printf("mx in a: %d\ncount<0 in b: %d\naverage: %f\n", mx_array(N, a), count_array(N, b), average);
// }







// На 5
#include <stdio.h>

int suco_array(int n, int array[]) {
    int sum=0, count=0;
    for (int i = 0; i < n; i++) {
        sum+=array[i];
        count+=1;
    }
    return sum/count;
}

int mx_array(int n, int array[]) {
    int mx=0,mx_ind=0;
    for (int i = 0; i < n; i++) {
        if (mx<array[i]) {
            mx=array[i];
            mx_ind=i;
        }
    }
    return mx_ind;
}

int mn_array(int n, int array[]) {
    int mn=999999,mn_ind=0;
    for (int i = 0; i < n; i++) {
        if (mn>array[i]) {
            mn=array[i];
            mn_ind=i;
        }
    }
    return mn_ind;
}

void print_array(int n, int array[n]) {
    printf("mas: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[10] = {324, 123, 567, 437, 878, 654, 132786, 5763, 654, 334},mx,mn,count=0;
    float average=suco_array(10, array);
    printf("average=%f\n",average);
    for (int i = 0,n=10; i < n; i++) {
        if (array[i]<average) {
            count+=1;
        }
    }
    int ind_mx,ind_mn;
    mx=array[mx_array(10,array)];
    mn=array[mn_array(10,array)];
    ind_mx=mx_array(10,array);
    ind_mn=mn_array(10,array);
    printf("mn=%d, mx=%d\n ind_mn=%d, ind_mx=%d\n count=%d\n",mn,mx,ind_mn,ind_mx,count);
    print_array(10,array);
    for (int st=ind_mn,en=ind_mx-1; (st!=en); st++) {
        array[st+1]=0;
    }
    print_array(10,array);
}
