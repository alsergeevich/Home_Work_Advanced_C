#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N); // Читаем количество чисел

    int current_number;
    int max_number = 0; // Переменная для хранения максимального числа
    int max_count = 0;  // Переменная для хранения количества вхождений максимума

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &current_number); // Читаем текущее число

        if (i == 0 || current_number > max_number)
        {
            max_number = current_number; // Обновляем максимум
            max_count = 1;               // Сбрасываем счетчик
        }
        else if (current_number == max_number)
        {
            max_count++; // Увеличиваем счетчик, если число равно максимуму
        }
    }

    printf("%d\n", max_count); // Выводим количество вхождений максимума
    return 0;
}