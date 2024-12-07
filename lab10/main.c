#include <stdio.h>
#include "functions.h"

int main(){
    int n,sum=0,min;
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
