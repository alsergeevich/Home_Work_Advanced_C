#include <stdint.h>

typedef struct list
{
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

size_t totalMemoryUsage(list *head)
{
    if (head == NULL) // проверяем на пустоту
        return 0;

    size_t sum_memory = 0; // переменная суммы объёма памяти
    list *temp = head;     // создаём указатель на начало списка
    while (temp != NULL)   // пока не конец списка
    {
        sum_memory += temp->size; // суммируем объём памяти

        temp = temp->next; // переходим к следующему элементу
    }
    return sum_memory; // возвращаем сумму объёма памяти используемую списком
}