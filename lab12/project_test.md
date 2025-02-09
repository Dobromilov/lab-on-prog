```c
#include <stdio.h>
#include <stdlib.h>

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

void selectionSort(struct Student arr[],int size){
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
}

void printPerson(struct Student p){
    printf("name: %s; ",p.name);
    printf("math: %d; ",p.math);
    printf("phy: %d; ",p.phy);
    printf("inf: %d; ",p.inf);
    printf("total: %d; \n",p.total);
}

int main(void){
    const int size=100;
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

    selectionSort(people,size);
    
    printf("\naSort array: \n");
    for (int i = 0; i < size; i++) {
        printPerson(people[i]);
    }

}
```
