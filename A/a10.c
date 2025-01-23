#include <stdio.h>

int extractExp(float num) {
    // union применяем для преобразования float в целое число, чтобы потом извлечь экспоненту
    union {
        float f;
        unsigned int i;
    } u;
    
    u.f = num;
    
    // извлечение экспоненты (8 битов, начиная с 23-го бита)
    int exp = (u.i >> 23) & 0xFF;
    
    // можно получить истиное значение экспоненты вычитанием смещения 127. Это смещение используется для хранения экспоненты в формате IEEE 754
    //exp -= 127;
    //в задании это делать не надо. Просто извлечь экспоненту. Значит не делаем.
    
    return exp;
}

int main() {
    float num;
    scanf("%f", &num);
    
    int exp = extractExp(num);
    printf("%d\n", exp);
    
    return 0;
}