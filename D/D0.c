/*
Дана строка, состоящая из английских букв и пробелов. В конце строки символ точка. Все слова разделены одним пробелом. 
Необходимо составить из слов односвязный список и упорядочить по алфавиту. 
Список необходимо удалить в конце программы. Для сравнение строк можно использовать strcmp. 
Необходимо использовать данную структуры организации списка.
struct list {
char word[20];
struct list *next;
}
Необходимо реализовать односвязный список и обслуживающие его функции.

add_to_list
 swap_elements
 print_list
 delete_list
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 200


typedef struct list {
    char word[20];
    struct list *next;
    
} list_t;


list_t* create_new_element (char* word) {
    
    list_t* new_element = malloc(sizeof(list_t));
    int size = sizeof(new_element->word);
    if (new_element == NULL) {
        return NULL;
    }
    new_element->next = NULL;
    strncpy(new_element->word, word, sizeof(new_element->word) - 1);
    new_element->word[sizeof(new_element->word) - 1] = '\0';
    return new_element;
}

void add_to_list (list_t** head, char* word) {
    list_t* new_element = create_new_element(word);
    if (new_element == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_element;
        return;
    } else {
        list_t* current = *head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = new_element;
    }
}

void swap_elements(list_t* a, list_t* b) {
    char temp[20];
    strcpy(temp, a->word);
    strcpy(a->word, b->word);
    strcpy(b->word, temp);
}

void print_list(list_t* head) {
    list_t* temp = head;
    while (temp != NULL) {
        printf("%s", temp->word); 
        if (temp->next != NULL) {
            printf(" "); 
        }
        temp = temp->next;
    }
    printf("\n"); 
}


void sort_list(list_t** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    int swapped;
    list_t *current;

    do {
        swapped = 0;
        current = *head;

        while (current->next != NULL) {
            if (strcmp(current->word, current->next->word) > 0) {
                swap_elements(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

void delete_list(list_t* head) {
    list_t* current = head;
    list_t* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

char* read_line() {
    size_t capacity = 100; 
    size_t length = 0;     
    char* buffer = malloc(capacity * sizeof(char));
    if (!buffer) return NULL;

    int c;
    while ((c = getchar()) != EOF && c != '.') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            buffer = realloc(buffer, capacity * sizeof(char));
            if (!buffer) return NULL;
        }
        buffer[length++] = c;
    }
    buffer[length] = '\0'; 
    return buffer;
}

int main() {
    
    

    
    char* words = read_line();
    

    list_t* list = NULL;
    // Разбиваем строку на слова
    char* word = strtok(words, " ");
    while (word != NULL) {
        add_to_list(&list, word);
        word = strtok(NULL, " ");
    }
    free(words);
    
    sort_list(&list);
    print_list(list);

    delete_list(list);
}
