#include "functions.h"

int mn(int time,int mn){
    if (mn>time){
        mn=time;
        return mn;
    } else {
        return mn;
    }
}

int sm(int term,int sum){
        sum+=term;
    return sum;
}

int minutes(int x){
    return x%60;
}

int hour(int x){
    return x/60;
}