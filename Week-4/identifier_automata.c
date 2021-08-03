#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define INVALID -1
#define END_STATE -2
#define TERMINATOR '\0'

int is_letter(char l) { return isalpha(l) || l == '_'; }

int state_0(char c) {
    int new_state = INVALID;

    if (is_letter(c)) new_state = 1;

    return new_state;
}

int state_1(char c) {
    int new_state = INVALID;

    if (c == TERMINATOR)
        new_state = END_STATE;

    else if (is_letter(c) || isdigit(c))
        new_state = 1;

    return new_state;
}

typedef int (*automata)(char);

int identifier_automata(char *str) {
    automata states[2] = {&state_0, &state_1};

    int current_state = 0, i = 0;
    while (1) {
        current_state = states[current_state](str[i++]);
        if (current_state == INVALID) return 0;
        if (current_state == END_STATE) return 1;
    }

    return 0;
}

int main(int argc, char const *argv[]) {
    char *test_cases[10] = {
        "i",          "rank1", "MAX",      "max",     "Min",
        "class_rank", "a's",   "fact rec", "2sqroot", "class,rank",
    };

    for (int i = 0; i < 10; i++) {
        printf("%s\t", test_cases[i]);

        if (identifier_automata(test_cases[i]))
            printf("VALID\n");
        else
            printf("INVALID\n");
    }

    return 0;
}
