#include "functions.h" 

#define DEFAULT_EPS 1e-6 //значение точности для тестов

int main(int argc, char *argv[]) {
    if (argc == 1 || strcmp(argv[1], "--help") == 0) { // Если пользователь запросил справку
        printf("valid keys:\n");
        printf("--roots --e <eps> : print the abscissas of the intersection points of the curves with accuracy <eps>\n");
        printf("--iterations --e <eps> : print the number of iterations when searching for roots with accuracy <eps>\n");
        printf("--area --e <eps> : print the area enclosed by curves with accuracy <eps>\n");
        printf("--test-root       : test the function root\n");
        printf("--test-integral   : test the function integral\n");
        return 0;
    }

    if (strcmp(argv[1], "--roots") == 0 && argc == 4 && strcmp(argv[2], "--e") == 0) { // Если выбран режим вывода точек пересечения
        double eps = atof(argv[3]); // Преобразуем строку с точностью в число
        int iterations;


        double x1 = root(f1, f3, df1, df3, 0.5, 4, eps, &iterations); // Находим точку пересечения f1 = f3
        printf("abscissa of intersection point f1 = f3: %.6f (iterations: %d)\n", x1, iterations);

        double x2 = root(f1, f2, df1, df2, 0.5, 4, eps, &iterations); // Находим точку пересечения f1 = f2
        printf("abscissa of intersection point f1 = f2: %.6f (iterations: %d)\n", x2, iterations);

        
        double x3 = root(f2, f3, df2, df3, 0.5, 4, eps, &iterations); // Находим точку пересечения f2 = f3
        printf("abscissa of intersection point f2 = f3 : %.6f (iterations: %d)\n", x3, iterations);


    } else if (strcmp(argv[1], "--iterations") == 0 && argc == 4 && strcmp(argv[2], "--e") == 0) { // Если выбран режим вывода числа итераций
        double eps = atof(argv[3]); // Преобразуем строку с точностью в число
        int iterations;

        double x1 = root(f1, f3, df1, df3, 0.5, 4, eps, &iterations); // Находим точку пересечения f1 = f3
        printf("number of iterations for f1 = f3: %d\n", iterations);

        double x2 = root(f1, f2, df1, df2, 0.5, 4, eps, &iterations); // Находим точку пересечения f1 = f2
        printf("number of iterations for f1 = f2: %d\n", iterations);

        double x3 = root(f2, f3, df2, df3, 0.5, 5, eps, &iterations); // Находим точку пересечения f2 = f3
        printf("number of iterations for f2 = f3: %d\n", iterations);

    } else if (strcmp(argv[1], "--area") == 0 && argc == 4 && strcmp(argv[2], "--e") == 0) { // Если выбран режим вычисления площади
        double eps = atof(argv[3]); // Преобразуем строку с точностью в число

        int iterations;
        double x1 = root(f1, f3, df1, df3, 0.5, 4, eps, &iterations); // Находим точку пересечения f1 = f3
        double x2 = root(f1, f2, df1, df2, 0.5, 4, eps, &iterations); // Находим точку пересечения f1 = f2
        double x3 = root(f2, f3, df2, df3, 0.5, 5, eps, &iterations); // Находим точку пересечения f2 = f3
        

        // Вычисляем площадь фигуры образованной уравнениями f1, f2, f3
        double total_area = calculate_area(x1, x2, x3, f1, f2, f3, eps);
        
        printf("area bounded by curves: %.6f\n", total_area);
        
    } else if (strcmp(argv[1], "--test-root") == 0) { // Если выбран тест функции root
        int iterations;
        double x1 = root(f1, f3, df1, df3, 0.5, 5, DEFAULT_EPS, &iterations); // Тестируем root для f1 = f3
        printf("Test root:\n");
        printf("Root f1 = f3: %.6f (iterations: %d)\n", x1, iterations);

        double x2 = root(f1, f2, df1, df2, 0.5, 5, DEFAULT_EPS, &iterations); // Тестируем root для f1 = f2
        printf("Root f1 = f2: %.6f (iterations: %d)\n", x2, iterations);

        double x3 = root(f2, f3, df2, df3, 0.5, 5, DEFAULT_EPS, &iterations); // Тестируем root для f2 = f3
        printf("Root f2 = f3: %.6f (iterations: %d)\n", x3, iterations);
    } else if (strcmp(argv[1], "--test-integral") == 0) { // Если выбран тест функции integral
        double result1 = integral(f1, 0.85, 3.84, DEFAULT_EPS); // Тестируем integral для f1(x)
        printf("Test integral: Sf1(x)dx = %.6f\n", result1);
        double result2 = integral(f2, 3.24, 3.84, DEFAULT_EPS); // Тестируем integral для f2(x)
        printf("Test integral: Sf2(x)dx = %.6f\n", result2);
        double result3 = integral(f3, 0.85, 3.24, DEFAULT_EPS); // Тестируем integral для f3(x)
        printf("Test integral: Sf3(x)dx = %.6f\n", result3);
    } else { // Если команда некорректна
        printf("incorrect parameters. use --help for help.\n");
    }

    return 0; 
}