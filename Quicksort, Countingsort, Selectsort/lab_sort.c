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
