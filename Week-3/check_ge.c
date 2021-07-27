#include <stdio.h>

int is_ge(char *str) { return str[0] == '>' && str[1] == '='; }

int main(int argc, char const *argv[]) {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    if (is_ge(str))
        printf("Valid Finite Automata\n");
    else
        printf("Invalid Finite Automata\n");

    return 0;
}
