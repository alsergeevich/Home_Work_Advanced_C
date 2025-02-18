#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Объявление функций из условия задачи
double f1(double x);
double f2(double x);
double f3(double x);

// Объявление производных функций
double df1(double x);
double df2(double x);
double df3(double x);

// Функция для нахождения точек пересечения методом Ньютона
double root(double (*f)(double), double (*g)(double), double (*df)(double), double (*dg)(double), double a, double b, double eps, int *iterations);

// Функция для вычисления интеграла методом трапеций
double integral(double (*func)(double), double a, double b, double eps);

// Функция для вычисления площади между кривыми
double calculate_area(double x1, double x2, double x3, double (*f1)(double), double (*f2)(double), double (*f3)(double), double eps);

#endif // FUNCTIONS_H