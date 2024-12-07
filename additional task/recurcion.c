#include <stdio.h>
#include <math.h>

// Функция для вычисления факториала
double factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// Рекурсия для вычисления финального значения
double chx(double x, int n, double E) {
    double term = pow(x, 2 * n) / factorial(2 * n);
    if (term < E) {
        return term;
    } else {
        return term + chx(x, n + 1, E);
    }
}

int main() {
    double x, E = 0.0001;
    printf("Введите x: ");
    scanf("%lf", &x);
    double result = chx(x, 0, E);
    printf("Приближённое значение cosh(%lf) = %lf\n", x, result);
    return 0;
}

