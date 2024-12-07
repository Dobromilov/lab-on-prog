#include <stdio.h>
struct time
{
    int hour;
    int minutes;
};

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

int main(){
    int n,sum,min;
    min=10000000;
    scanf("%d",&n);
    for (int i=0; i<n; i++){
        struct time value;
        
        scanf("%d",&value.hour);
        scanf("%d",&value.minutes);
    
        sum=sm(value.hour*60+value.minutes,sum);
        min=mn(value.hour*60+value.minutes,min);
    }
    
    printf("sum=%d:%d min=%d:%d\n",hour(sum),minutes(sum),hour(min),minutes(min));
    return 0;
}

