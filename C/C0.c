#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Функция для подсчета уникальных трехзначных чисел
int count_unique_three_digit_numbers(const char *N) {
    int len = strlen(N); // Вычисляем длину введенного числа через длину строки
    if (len < 3) return 0; // Если длина меньше 3, возвращаем 0

    int unique_count = 0; // Количество уникальных трехзначных чисел
    int used[1000] = {0}; // Массив для отслеживания уникальных трехзначных чисел

    // Генерируем все возможные комбинации из 3 цифр
    for (int i = 0; i < len - 2; ++i) {
        for (int j = i + 1; j < len - 1; ++j) {
            for (int k = j + 1; k < len; ++k) {
                // Формируем трехзначное число
                int number = (N[i] - '0') * 100 + (N[j] - '0') * 10 + (N[k] - '0');
                if(number < 100) continue; // Отбрасываем числа меньше 100
                if (!used[number]) { // Если число ещё не попадалось то ставим в ячейке с номером == числу 1
                    used[number] = 1;
                    unique_count++; // Увеличиваем счетчик уникальных чисел
                }
            }
        }
    }

    return unique_count;
}

int main() {
    char N[1000]; // Буфер для числа в виде строки
    scanf("%s", N);

    // Подсчитываем количество уникальных трехзначных чисел
    int result = count_unique_three_digit_numbers(N);

    // Выводим результат
    printf("%d\n", result);

    return 0;
}
//12345678909876543210123456789