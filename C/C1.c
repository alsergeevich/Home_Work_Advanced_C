/*
Префикс и суффикс
На стандартном потоке ввода задаются две символьные строки, разделённые символом перевода строки. 
Каждая из строк не превышает по длине 104. В строках не встречаются пробельные символы. 
На стандартный поток вывода напечатайте два числа, разделённых пробелом: 
первое число — длина наибольшего префикса первой строки, являющегося суффиксом второй; 
второе число — наоборот, длина наибольшего суффикса первой строки, являющегося префиксом второй. 
Сравнение символов проводите с учётом регистра (т.е. символы 'a' и 'A' различны).
Примеры
Входные данные
don't_panic
nick_is_a_mastodon
Результат работы
3 3
Входные данные
monty_python
python_has_list_comprehensions
Результат работы
0 6
*/



#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000

int findMaxPrefixSuffix(char *s1, char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int maxLen = 0;

    for (int i = 1; i <= len1 && i <= len2; i++) {
        if (strncmp(s1, s2 + len2 - i, i) == 0) {
            maxLen = i;
        }
    }

    return maxLen;
}

int findMaxSuffixPrefix(char *s1, char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int maxLen = 0;

    for (int i = 1; i <= len1 && i <= len2; i++) {
        if (strncmp(s1 + len1 - i, s2, i) == 0) {
            maxLen = i;
        }
    }

    return maxLen;
}

int main() {
    char s1[MAX_LEN + 1], s2[MAX_LEN + 1];
    
    scanf("%s", s1);
    scanf("%s", s2);

    int prefixSuffix = findMaxPrefixSuffix(s1, s2);
    int suffixPrefix = findMaxSuffixPrefix(s1, s2);

    printf("%d %d\n", prefixSuffix, suffixPrefix);

    return 0;
}


