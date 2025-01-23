/*
Упаковать массив
В программе реализована структура данных:
struct pack_array {
uint32_t array; // поле для хранения упакованного массива из 0 и 1
uint32_t count0 : 8; // счетчик нулей в array
uint32_t count1 : 8; // счетчик единиц в array
}
Необходимо реализовать программу, которая упаковывает переданный ей массив из 32-ух элементов 0 и 1 в указанную структуру данных.
Функция должна строго соответствовать прототипу:

void array2struct(int [], struct pack_array *)
*/

#include <stdio.h>
#include <stdint.h>

struct pack_array
{
    uint32_t array;      // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8; // счетчик нулей в array
    uint32_t count1 : 8; // счетчик единиц в array
};

uint32_t pow_ (uint32_t base, uint32_t exp) { // функция возведения в степень
    uint32_t result = 1;
    for (uint32_t i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

void array2struct(int array[], struct pack_array *pack) {
    pack->array = 0; // обнуляем переменные структуры
    pack->count0 = 0;
    pack->count1 = 0;
    for (uint32_t i = 0; i < 32; i++) {
        
        if (array[i] == 0) { // если элемент массива равен 0, то увеличиваем счетчик нулей
            pack->count0++;
        } else { // если элемент массива равен 1, то увеличиваем счетчик единиц и упаковываем в переменную array
            pack->array += array[i] * pow_(2, 31 - i);
            pack->count1++;
        }
    }
}

int main(void) {
    int array[32] = {0,};
    for(int i = 0; i < 32; i++) {
        scanf("%d", &array[i]);
    }
    struct pack_array pack;
    array2struct(array, &pack);
    printf("%u %u %u", pack.array, pack.count0, pack.count1);

}
