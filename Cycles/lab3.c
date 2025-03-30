/*6)  поиск простого числа
#include<stdio.h>

int main()
{
  int a, s = 0;
    scanf("%d", &a);
    for (int n = 2; n < a; n++) {
        if (a % n == 0) {
            s = 1;
            break;
        }
    }
    printf("%d",s);
}*/


/*7) поиск простого числа при помощи while
#include<stdio.h>
int main()
{
	int a;
	scanf("%d",&a);
	int n=2, flag = 0;
	while(a%n!=0){
 		n++;
		if (n==a)
		{
			flag = 1;
			break;
		};
	}
	printf("%d",flag);
}*/

/*8) факториал числа

#include<stdio.h>
int main()
{
	int s=1,n;
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	{
		s = s * i;
	}
	printf("%d",s);
}
*/


/*9)наибольшая цифра в ввиденном числе
#include <stdio.h>
int main() {
	int a, k, s = -1;
	scanf("%d", &a);
    	for (int n = a; n != 0; n = n / 10) {
        	k = n % 10;
        	if (k > s) {
            		s = k;
        	}
    	}
    	printf("%d", s);
}
*/

/*10)переворачивание числа

#include <stdio.h>
int main() {
    int s = 0, n, k = 0;
    scanf("%d", &n);
    for (s = 0; n != 0; n = n / 10) {
        k = n % 10;
        s = s * 10 + k;
    }
    printf("%d", s);
}
*/
