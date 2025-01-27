#include <stdint.h>

typedef struct list
{
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

uint64_t findMaxBlock(list *head)
{
    if (head == NULL)
        return 0; // проверяем на пустоту
    uint64_t addr = 0;
    size_t max = 0;
    list *temp = head; // создаём указатель на начало списка
    while (temp != NULL)
    { // пока не конец списка
        if (temp->size > max)
        {
            max = temp->size;
            addr = temp->address;
        }

        temp = temp->next; // переходим к следующему элементу
    }
    return addr; // возвращаем адрес
}