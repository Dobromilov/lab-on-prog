#include <stdio.h>
#include <math.h>
/*
1)
int main(){
	int a;
	scanf("%d",&a);
	if (a%400==0){
		printf("YES");
	} else if (a%100==0 && a%400!=0){
		printf("NO");
	} else if (a%4==0){
		printf("YES");
	} else {
		printf("NO");
	}

}*/



/*
2)
int main(){
	float temperature;
	char sim;
	char str[]="fcFC";
	printf("Input temperature: ");
	scanf("%f%c",&temperature,&sim);
	if (sim == str[1] || sim == str[3]) {
		printf("%.1ff",temperature*1.8+32);
	} else if (sim == str[0] || sim == str[2]) {
		printf("%.1fc",(temperature-32)/1.8);
	} else if (sim!=str[0] && sim!=str[1]) {
		printf("Output error");
	}
}*/


/*
3.1)
int main() {
	float x,y;
	printf("x: ");
	scanf("%f",&x);
	printf("y: ");
	scanf("%f",&y);
	if (y>=-x && x<=1 && y<=1){
		printf("Yes");
	} else {
		printf("No");
	}
}
*/



/*
3.2) для душевного спокойствия еще сделал
*/
int main(){
	float x,y;
	scanf("%f",&x);
	scanf("%f",&y);
	if ( (pow(x,2)+pow(y,2)<1) && (pow(x,2)+pow(y,2)>0.25) && (x>0) && (y>0) ){
		printf("Yes");
	} else {
		printf("No");
	}

}
