/*
Польская запись
Необходимо вычислить выражение написанное в обратной польской записи. 
На вход подается строка состоящая из целых, неотрицательных чисел и арифметических
 символов. В ответ единственное целое число - результат.
 Примеры
Входные данные
3 4 +.
Результат работы
7
Входные данные
1 2 + 4 × 3 +.
Результат работы
15
Входные данные
100 25 + 25 /.
Результат работы
5
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int *items;
    int top;
    int size;
} Stack;

void initStack(Stack *stack, int size) {
    stack->items = (int *)malloc(size * sizeof(int));
    stack->top = -1;
    stack->size = size;
}

void push(Stack *stack, int value) {
    stack->items[++stack->top] = value;
}

int pop(Stack *stack) {
    return stack->items[stack->top--];
}

int operation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) exit(1); // Просто завершаем программу при делении на ноль
            return a / b;
        default: exit(1); // При неизвестной операции завершаем программу
    }
}

int solution_of_expression(char *expression) {
    Stack stack;
    initStack(&stack, 100);

    const char *token = strtok(expression, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            push(&stack, atoi(token));
        } else if (strchr("+-*/", token[0]) != NULL) {
            int b = pop(&stack); //извлекаем элемент из стека
            int a = pop(&stack); //извлекаем элемент из стека
            int result = operation(a, b, token[0]); // применяем операцию к двум числам и помещаем результат в стек
            push(&stack, result);
        } else if (strcmp(token, ".") == 0) {
            break;
        }
        token = strtok(NULL, " ");
    }

    int result = pop(&stack);
    free(stack.items);
    return result;
}

int main() {
    char numeric_expression[256];
    fgets(numeric_expression, sizeof(numeric_expression), stdin);

    size_t len = strlen(numeric_expression);

    // Удаляем символ новой строки, если он есть
    if (len > 0 && numeric_expression[len - 1] == '\n') {
        numeric_expression[len - 1] = '\0';
    }

    printf("%d\n", solution_of_expression(numeric_expression));
    return 0;
}