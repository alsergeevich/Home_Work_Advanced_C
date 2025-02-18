#include "functions.h"
#include <math.h>

// Функции из условия задачи
double f1(double x) { return 0.6 * x + 3; }
double f2(double x) { return pow(x - 2, 3) - 1; }
double f3(double x) { return 3 / x; }

// Производные функций
double df1(double x) { return 0.6; }
double df2(double x) { return 3 * pow(x - 2, 2); }
double df3(double x) { return -3 / (x * x); }

// Функция для нахождения точки пересечения методом Ньютона
double root(double (*f)(double), double (*g)(double), double (*df)(double), double (*dg)(double), double a, double b, double eps, int *iterations) {
    int max_iter = 1000; // Максимальное количество итераций для метода Ньютона
    int iter = 0; //количество итераций для нахождения точки пересечения методом Ньютона, через неё iterations каждый вызов получает новое значение 


    double x = (a + b) / 2; // Начальное приближение: середина интервала [a, b]
    while (iter < max_iter) {
        double numerator = f(x) - g(x); // Вычисляем числитель формулы метода Ньютона
        double denominator = df(x) - dg(x); // Вычисляем знаменатель формулы метода Ньютона


        double next_x = x - numerator / denominator; // Обновляем значение x по формуле метода Ньютона

        if (next_x < a || next_x > b) { // Если новое приближение выходит за пределы интервала, корректируем его
            next_x = x - 0.5 * numerator / denominator;
        }

        if (fabs(next_x - x) < eps) { // Если изменение x меньше заданной точности, считаем, что решение найдено
            *iterations = iter + 1; // Увеличиваем счетчик итераций
            return next_x; 
        }

        x = next_x; // Обновляем x для следующей итерации
        iter++;
    }
}


// Функция для вычисления интеграла методом трапеций
double integral(double (*func)(double), double a, double b, double eps) {
    int n = 100; // Начальное количество отрезков для разбиения интервала
    double h = (b - a) / n; // Шаг разбиения интервала
    double sum = 0.5 * (func(a) + func(b)); // Начальная сумма для метода трапеций

    for (int i = 1; i < n; i++) { // Вычисляем сумму значений функции во внутренних точках
        sum += func(a + i * h);
    }

    double integral_val = h * sum; // Вычисляем первое приближение интеграла

    double prev_integral = 0;          // Переменная для хранения предыдущего значения интеграла
    do {                               // Цикл для увеличения точности до достижения заданной погрешности
        prev_integral = integral_val;  // Сохраняем текущее значение интеграла
        n *= 2;                        // Удваиваем количество отрезков
        h = (b - a) / n;               // Обновляем шаг разбиения
        sum = 0.5 * (func(a) + func(b)); // Обнуляем сумму для нового разбиения

        for (int i = 1; i < n; i++) { // Вычисляем новую сумму значений функции
            sum += func(a + i * h);
        }

        integral_val = h * sum; // Вычисляем новое значение интеграла
    } while (fabs(integral_val - prev_integral) > eps); 

    return integral_val; // Возвращаем вычисленное значение интеграла
}

// Функция для вычисления площади между кривыми
double calculate_area(double x1, double x2, double x3, double (*f1)(double), double (*f2)(double), double (*f3)(double), double eps) {
    
    double total_area = 0; //переменная для общей площади фигуры

    double integral_f1 = integral(f1, x1, x2, eps); // Вычисляем интеграл функции f1 по заданным точкам [x1, x2]
    double integral_f2 = integral(f2, x3, x2, eps); // Вычисляем интеграл функции f2 по заданным точкам [x3, x2]
    double integral_f3 = integral(f3, x1, x3, eps); // Вычисляем интеграл функции f3 по заданным точкам [x1, x3]

    total_area = integral_f1 - integral_f2 - integral_f3; //вычисляем площадь фигуры

    return total_area;
}